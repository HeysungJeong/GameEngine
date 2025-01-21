#include "GameEngine.h"
#include <iostream>

#define FPS 60
const int FRAME_DELAY = 1000 / FPS;		//16

GameEngine::GameEngine()
	: window(nullptr), renderer(nullptr), isRunning(false)
	, frameStart(0), frameTime(0) 
{
	//player = { 100, 100, 50, 50 };
	//obstacle = { 300, 100, 50, 50 };
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

	audioManager = new AudioManager();
	if (!audioManager->Initialize())
	{
		return false;
	}

	//audioManager->LoadSound("../../../resource/예감 그레이.mp3", "sound1");
	audioManager->LoadMusic("../../../resource/aa.mp3");

	isRunning = true;
	return true;
}

void GameEngine::Run()
{
	audioManager->PlayMusic();
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
		//창 닫기 버튼을 누루면 발생하는 이벤트
		if (event.type == SDL_QUIT)
			isRunning = false;

		if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				isRunning = false;
				break;
			case SDLK_SPACE:
				audioManager->PlaySound("sound1");
				break;
			default:
				break;
			}
		}
	}
}

void GameEngine::Update()
{
	// 충돌 감지 및 처리
	/*if (CheckAABBCollision(player, obstacle)) {
		std::cout << "Collision detected!" << std::endl;
	}*/
	//animation->Update();
}

void GameEngine::Render()
{
	//검정색으로 칠함
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	// 플레이어 렌더링
	//SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	//SDL_RenderFillRect(renderer, &player);

	// 장애물 렌더링
	//SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	//SDL_RenderFillRect(renderer, &obstacle);

	// 텍스처 렌더링
	//animation->Render(renderer, texture, 200, 150);
	//타일 렌더링
	//tileMap->Render(renderer);
	//랜더링 결과를 화면에 출력
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
