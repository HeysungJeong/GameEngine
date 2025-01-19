#include "GameEngine.h"
#include <iostream>

GameEngine::GameEngine()
	: window(nullptr)
	, renderer(nullptr)
	, isRunning(false)
{
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
	isRunning = true;
	return true;
}

void GameEngine::Run()
{
	while (isRunning)
	{
		HandleEvents();
		Update();
		Render();
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
	//검정색으로 칠함
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	//빨간색 직사각형 그리기
	SDL_Rect rect = { 200,150,400,300 };
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(renderer, &rect);

	//랜더링 결과를 화면에 출력
	SDL_RenderPresent(renderer);
}
