#pragma once

#include <vector>
#include <SDL.h>

class Animation {
public:
	Animation(int frameWidth, int frameHeight, int numFrames, Uint32 frameDuration);

	void AddFrame(int x, int y);
	void Update();
	void Render(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y);

private:
	std::vector<SDL_Rect> frames;
	int currentFrame;
	int frameWidth;
	int frameHeight;
	int numFrames;
	Uint32 frameDuration;
	Uint32 lastFrameTime;
};