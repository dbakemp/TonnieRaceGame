#ifndef CMAP_H
#define CMAP_H

#include <SDL.h>
#include <iostream>
#include "CEntityWaypoint.h"
<<<<<<< HEAD
#include "CEntityPowerup.h"
=======
#include "CEntitySpawn.h"
>>>>>>> master

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
<<<<<<< HEAD
	std::vector<CEntityPowerup*> powerups;

=======
	std::vector<CEntitySpawn*> availableSpawns;
	std::vector<CEntitySpawn*> takenSpawns;
	CEntitySpawn* GetSpawn();
>>>>>>> master
private:
};

#endif 
