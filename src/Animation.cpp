#include "Animation.h"

Animation::Animation(int frameWidth, int frameHeight, int numFrames, Uint32 frameDuration)
	: frameWidth(frameWidth), frameHeight(frameHeight)
	, numFrames(numFrames), frameDuration(frameDuration)
	, currentFrame(0), lastFrameTime(0)
{}

void Animation::AddFrame(int x, int y)
{
	SDL_Rect frame;
	frame.x = x;
	frame.y = y;
	frame.w = frameWidth;
	frame.h = frameHeight;
	frames.push_back(frame);
}

void Animation::Update()
{
	Uint32 currentTime = SDL_GetTicks();
	if (currentTime > lastFrameTime + frameDuration)
	{
		currentFrame = (currentFrame + 1) % numFrames;
		lastFrameTime = currentTime;
	}
}

void Animation::Render(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y)
{
	SDL_Rect destRect = { x, y, frameWidth, frameHeight };
	SDL_RenderCopy(renderer, texture, &frames[currentFrame], &destRect);
}