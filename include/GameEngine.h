#ifndef GAMEENGINE_H
#define GAMEENGINE_H

//�𵨸� ��ȯ(Model Transformation) : ��ü�� ��ġ, ũ��, ȸ���� �����մϴ�.
//�� ��ȯ(View Transformation) : ī�޶��� ��ġ�� ������ �����մϴ�.
//���� ��ȯ(Projection Transformation) : 3D ��ǥ�� 2D ȭ�鿡 �����մϴ�.
//����Ʈ ��ȯ(Viewport Transformation) : ������ ��ǥ�� ���� ȭ�� ��ǥ�� ��ȯ�մϴ�.

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