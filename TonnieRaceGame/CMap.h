#ifndef CMAP_H
#define CMAP_H

#include <SDL.h>
#include <iostream>
#include "CEntityWaypoint.h"
#include "CEntityPowerup.h"
#include "CEntitySpawn.h"
#include "CEntityCheckpoint.h"

class CEntityCar;

class CMap
{
public:
	CMap(CEngine* engine);
	~CMap();

	void CheckPositions();

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

	CEntityCheckpoint* GetCheckpointByIndex(int index);

	std::vector<CEntityWaypoint*> waypoints;
	std::vector<CEntitySpawn*> availableSpawns;
	std::vector<CEntitySpawn*> takenSpawns;
	std::vector<CEntityCheckpoint*> checkpointsList;
	std::vector<CEntityCar*> cars;
	std::vector<CEntityCar*> allCars;
	CEntitySpawn* GetSpawn();
private:
	CEngine* engine;
};

#endif
