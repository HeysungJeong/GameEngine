#include "GameEngine.h"
#include <iostream>

#define FPS 60
const int FRAME_DELAY = 1000 / FPS;		//16

GameEngine::GameEngine()
	: window(nullptr), renderer(nullptr), isRunning(false)
	, frameStart(0), frameTime(0) 
{
	player = { 100, 100, 50, 50 };
	obstacle = { 300, 100, 50, 50 };
}

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

	//if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
	//	std::cerr << "IMG_Init Error: " << IMG_GetError() << std::endl;
	//	return false;
	//}

	/*tileMap = new TileMap(32, 32, 26, 20);
	if (!tileMap->LoadTileSet("../../../resource/full_tilemap.png", renderer))
	{
		return false;
	}*/

	//Ÿ�ϸ� ����
	//for (int y = 0; y < 20; ++y)
	//{
	//	for (int x = 0; x < 26; ++x)
	//	{
	//		tileMap->SetTile(x, y, (x + y) % 4); //Ÿ�� id ����
	//	}
	//}
	// �ִϸ��̼� ����
	/*if (!LoadTexture("../../../resource/StupidRat.png")) {
		return false;
	}*/
	//animation = new Animation(128, 160, 5, 200);
	// ������ �ʺ�, ����, �� ������ ��, ������ ���� �ð� (�и���)
	//for (int i = 0; i < 5; ++i)
	//{
	//	animation->AddFrame(i * 128, 0);
	//}

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
	//if (animation)
	//{
	//	delete animation;
	//	animation = nullptr;
	//}
	//if (texture)
	//{
	//	SDL_DestroyTexture(texture);
	//	texture = nullptr;
	//}
	//if (tileMap)
	//{
	//	delete tileMap;
	//	tileMap = nullptr;
	//}
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
	//IMG_Quit();
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
			// �÷��̾� �̵� ó��
			case SDLK_UP:
				player.y -= 5;
				break;
			case SDLK_DOWN:
				player.y += 5;
				break;
			case SDLK_LEFT:
				player.x -= 5;
				break;
			case SDLK_RIGHT:
				player.x += 5;
				break;
			default:
				break;
			}
		}
	}
}

void GameEngine::Update()
{
	// �浹 ���� �� ó��
	if (CheckAABBCollision(player, obstacle)) {
		std::cout << "Collision detected!" << std::endl;
	}
	//animation->Update();
}

void GameEngine::Render()
{
	//���������� ĥ��
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	// �÷��̾� ������
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	SDL_RenderFillRect(renderer, &player);

	// ��ֹ� ������
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(renderer, &obstacle);

	// �ؽ�ó ������
	//animation->Render(renderer, texture, 200, 150);
	//Ÿ�� ������
	//tileMap->Render(renderer);
	//������ ����� ȭ�鿡 ���
	SDL_RenderPresent(renderer);
}

//bool GameEngine::LoadTexture(const char* filePath)
//{
//	SDL_Surface* tempSurface = IMG_Load(filePath);
//	if (tempSurface == nullptr) {
//		std::cerr << "IMG_Load Error: " << IMG_GetError() << std::endl;
//		return false;
//	}
//
//	texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
//	SDL_FreeSurface(tempSurface);
//
//	if (texture == nullptr) {
//		std::cerr << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
//		return false;
//	}
//	return true;
//}
