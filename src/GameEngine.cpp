#include "GameEngine.h"
#include <iostream>

#define FPS 60
const int FRAME_DELAY = 1000 / FPS;		//16

GameEngine::GameEngine()
	: window(nullptr)
	, renderer(nullptr)
	, isRunning(false)
	, frameStart(0)
	, frameTime(0) { }

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

		// FPS ��� ����
		frameCount++; // �������� ������ �� ����
		fpsTimer += frameTime; // ������ �ð� ����

		if (fpsTimer >= 1000) { // �� �ʸ��� FPS ���
			currentFPS = frameCount / (fpsTimer / 1000.0f); // �� ������ ���� FPS ���
			fpsTimer = 0;     // Ÿ�̸� �ʱ�ȭ
			frameCount = 0;   // ������ ī��Ʈ �ʱ�ȭ

			std::cout << "���� FPS: " << currentFPS << std::endl; // �ֿܼ� ���

			// ȭ�鿡 �ؽ�Ʈ�� ǥ���Ϸ��� SDL_ttf ���̺귯���� ����ؾ� ��.
			// ��: TTF_RenderText_Solid() �Լ� ��� ����.
		}
	}
}

void GameEngine::Shutdown()
{
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
			default:
				break;
			}
		}
	}
}

void GameEngine::Update()
{
}

void GameEngine::Render()
{
	//���������� ĥ��
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	//������ ���簢�� �׸���
	SDL_Rect rect = { 200,150,400,300 };
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(renderer, &rect);

	//������ ����� ȭ�鿡 ���
	SDL_RenderPresent(renderer);
}
