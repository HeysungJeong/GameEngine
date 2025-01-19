#ifndef GAMEENGINE_H
#define GAMEENGINE_H

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


};
#endif // GAMEENGINE_H