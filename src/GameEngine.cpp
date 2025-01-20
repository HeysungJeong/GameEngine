#include "GameEngine.h"
#include <iostream>

#define FPS 60
const int FRAME_DELAY = 1000 / FPS;		//16

GameEngine::GameEngine()
	: window(nullptr), renderer(nullptr), isRunning(false)
	, frameStart(0), frameTime(0), spriteWidth(128)
	, spriteHeight(160), currentFrame(0), totalFrames(4)
	, animationDelay(200), lastFrameTime(0){ }

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
	UpdateAnimation();
}

void GameEngine::Render()
{
	//검정색으로 칠함
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	// 텍스처 렌더링
	SDL_Rect srcRect = { currentFrame * spriteWidth, 0, spriteWidth, spriteHeight };
	SDL_Rect destRect = { 200,150, spriteWidth, spriteHeight };
	SDL_RenderCopy(renderer, texture, &srcRect, &destRect);

	//랜더링 결과를 화면에 출력
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

void GameEngine::UpdateAnimation()
{
	Uint32 currentTime = SDL_GetTicks();
	if (currentTime > lastFrameTime + animationDelay)
	{
		currentFrame++;
		if (currentFrame >= totalFrames)
		{
			currentFrame = 0;
		}
		lastFrameTime = currentTime;
	}
}
