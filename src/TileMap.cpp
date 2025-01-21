#include "TileMap.h"
#include <iostream>


TileMap::TileMap(int tileWidth, int tileHeight, int mapWidth, int mapHeight)
	: tileWidth(tileWidth), tileHeight(tileHeight), mapWidth(mapWidth)
	, mapHeight(mapHeight), tileSet(nullptr)
{
	map.resize(mapHeight, std::vector<int>(mapWidth, 0));
}

TileMap::~TileMap()
{
	if (tileSet) {
		SDL_DestroyTexture(tileSet);
	}
}

bool TileMap::LoadTileSet(const char* filePath, SDL_Renderer* renderer)
{
	SDL_Surface* tempSurface = IMG_Load(filePath);
	if (tempSurface == nullptr) {
		std::cerr << "IMG_Load Error: " << IMG_GetError() << std::endl;
		return false;
	}

	tileSet = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	if (tileSet == nullptr) {
		std::cerr << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
		return false;
	}
	return true;
}

void TileMap::SetTile(int x, int y, int tileID)
{
	if (x >= 0 && x < mapWidth && y >= 0 && y < mapHeight) {
		map[y][x] = tileID;
	}
}

void TileMap::Render(SDL_Renderer* renderer)
{
	static int temp = 0;
	temp %= 5;
	int w = 0, h = 0;
	if (SDL_QueryTexture(tileSet, NULL, NULL, &w, &h))
	{
		std::cerr << "Failed to query texture: " << SDL_GetError() << std::endl;
	}

	SDL_Delay(500);

	for (int y = 0; y < mapHeight; ++y) {
		for (int x = 0; x < mapWidth; ++x) {
			int tileID = map[y][x];
			SDL_Rect srcRect = { (tileID % (w / tileWidth)) * tileWidth, /*(tileID / (w / tileWidth))*/temp * tileHeight, tileWidth, tileHeight };
			SDL_Rect destRect = { x * tileWidth, y * tileHeight, tileWidth, tileHeight };
			SDL_RenderCopy(renderer, tileSet, &srcRect, &destRect);
		}
	}
	temp++;
}
