#ifndef CMAP_H
#define CMAP_H

#include <SDL.h>
#include <iostream>
#include "CEntityWaypoint.h"
#include "CEntityPowerup.h"
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
	SDL_Texture* spriteSheetPowerUps;

	int width;
	int height;
	int tileheight;
	int tilewidth;

	int laps;
	int checkpoints;

	std::vector<CEntityWaypoint*> waypoints;
	std::vector<CEntityPowerup*> powerups;
	std::vector<CEntitySpawn*> availableSpawns;
	std::vector<CEntitySpawn*> takenSpawns;
	CEntitySpawn* GetSpawn();
private:
};

#endif 
