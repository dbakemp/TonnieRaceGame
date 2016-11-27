#ifndef CMAP_H
#define CMAP_H

#include <SDL.h>
#include <iostream>

class CMap
{
public:
	CMap();
	~CMap();

	SDL_Texture* spriteSheet;
	std::string spriteSheetLocation;
	int spriteSheetColumns;
	int spriteSheetSpacing;
	int spriteSheetWidth;
	int spriteSheetHeight;
	int spriteSheetTileWidth;
	int spriteSheetTileHeight;

	int width;
	int height;
	int tileheight;
	int tilewidth;

	int laps;
	int checkpoints;

	int spawnX;
	int spawnY;
private:
};

#endif 
