#ifndef CMAP_H
#define CMAP_H

#include <SDL.h>
#include <iostream>
#include "CEntityWaypoint.h"
#include "CEntitySpawn.h"

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

	std::vector<CEntityWaypoint*> waypoints;
	std::vector<CEntitySpawn*> availableSpawns;
	std::vector<CEntitySpawn*> takenSpawns;
	CEntitySpawn* GetSpawn();
private:
};

#endif 
