#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <vector>

class TileMap {
public:
    TileMap(int tileWidth, int tileHeight, int mapWidth, int mapHeight);
    ~TileMap();

    bool LoadTileSet(const char* filePath, SDL_Renderer* renderer);
    void SetTile(int x, int y, int tileID);
    void Render(SDL_Renderer* renderer);

private:
    int tileWidth;
    int tileHeight;
    int mapWidth;
    int mapHeight;
    SDL_Texture* tileSet;
    std::vector<std::vector<int>> map;
};