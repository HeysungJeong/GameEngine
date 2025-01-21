#ifndef GAMEENGINE_H
#define GAMEENGINE_H

//모델링 변환(Model Transformation) : 객체의 위치, 크기, 회전을 설정합니다.
//뷰 변환(View Transformation) : 카메라의 위치와 방향을 설정합니다.
//투영 변환(Projection Transformation) : 3D 좌표를 2D 화면에 투영합니다.
//뷰포트 변환(Viewport Transformation) : 투영된 좌표를 실제 화면 좌표로 변환합니다.

#include <SDL.h>
#include <SDL_image.h>
#include "Animation.h"
#include "TileMap.h"
#include "Physics.h"

class GameEngine {
public:
	GameEngine();
	~GameEngine();
	bool Initialize(const char* title, int width, int height);
	void Run();
	void Shutdown();

private:
	SDL_Window*		window;
	SDL_Renderer*	renderer;
	SDL_Rect		player;
	SDL_Rect		obstacle;
	//SDL_Texture*	texture;
	//Animation*	animation;
	//TileMap*		tileMap;

	bool			isRunning;
	Uint32			frameStart;
	int				frameTime;

	void HandleEvents();
	void Update();
	void Render();
	//bool LoadTexture(const char* filePath);
	//void UpdateAnimation();
};
#endif // GAMEENGINE_H