#include "GameEngine.h"
#include <iostream>

#define FPS 60
const int FRAME_DELAY = 1000 / FPS;		//16

GameEngine::GameEngine()
	: window(nullptr), renderer(nullptr), texture(nullptr)
	, isRunning(false), frameStart(0), frameTime(0) { }

GameEngine::~GameEngine()
{
	Shutdown();
}

bool GameEngine::Initialize(const char* title, int width, int height)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return false;
	}

	window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED
		, width, height, SDL_WINDOW_SHOWN);
	if (window == nullptr)
	{
		std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr)
	{
		std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		return false;
	}

	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
		std::cerr << "IMG_Init Error: " << IMG_GetError() << std::endl;
		return false;
	}

	if (!LoadTexture("../../../resource/StupidRat.png")) {
		return false;
	}

	// �ִϸ��̼� ����
	animation = new Animation(128, 160, 5, 200);
	// ������ �ʺ�, ����, �� ������ ��, ������ ���� �ð� (�и���)
	for (int i = 0; i < 5; ++i)
	{
		animation->AddFrame(i * 128, 0);
	}

	isRunning = true;
	return true;
}

void GameEngine::Run()
{
	while (isRunning)
	{
		frameStart = SDL_GetTicks();

		HandleEvents();
		Update();
		Render();

		frameTime = SDL_GetTicks() - frameStart;
		if (FRAME_DELAY > frameTime)
		{
			SDL_Delay(FRAME_DELAY - frameTime);
		}
	}
}

void GameEngine::Shutdown()
{
	if (animation)
	{
		delete animation;
		animation = nullptr;
	}
	if (texture)
	{
		SDL_DestroyTexture(texture);
		texture = nullptr;
	}
	if (renderer)
	{
		SDL_DestroyRenderer(renderer);
		renderer = nullptr;
	}
	if (window)
	{
		SDL_DestroyWindow(window);
		window = nullptr;
	}
	IMG_Quit();
	SDL_Quit();
}

void GameEngine::HandleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		//â �ݱ� ��ư�� ����� �߻��ϴ� �̺�Ʈ
		if (event.type == SDL_QUIT)
			isRunning = false;

		if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				isRunning = false;
				break;
				//�߰� �Է�ó�� �� ��
			default:
				break;
			}
		}
	}
}

void GameEngine::Update()
{
	animation->Update();
}

void GameEngine::Render()
{
	//���������� ĥ��
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	// �ؽ�ó ������
	animation->Render(renderer, texture, 200, 150);

	//������ ����� ȭ�鿡 ���
	SDL_RenderPresent(renderer);
}

bool GameEngine::LoadTexture(const char* filePath)
{
	SDL_Surface* tempSurface = IMG_Load(filePath);
	if (tempSurface == nullptr) {
		std::cerr << "IMG_Load Error: " << IMG_GetError() << std::endl;
		return false;
	}

	texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	if (texture == nullptr) {
		std::cerr << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
		return false;
	}
	return true;
}
