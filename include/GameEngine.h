#ifndef GAMEENGINE_H
#define GAMEENGINE_H

//�𵨸� ��ȯ(Model Transformation) : ��ü�� ��ġ, ũ��, ȸ���� �����մϴ�.
//�� ��ȯ(View Transformation) : ī�޶��� ��ġ�� ������ �����մϴ�.
//���� ��ȯ(Projection Transformation) : 3D ��ǥ�� 2D ȭ�鿡 �����մϴ�.
//����Ʈ ��ȯ(Viewport Transformation) : ������ ��ǥ�� ���� ȭ�� ��ǥ�� ��ȯ�մϴ�.

#include <SDL.h>
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
	bool			isRunning;

	void HandleEvents();
	void Update();
	void Render();
};
#endif // GAMEENGINE_H