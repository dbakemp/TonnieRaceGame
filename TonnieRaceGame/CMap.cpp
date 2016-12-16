#include "CMap.h"

CMap::CMap()
{
}

CMap::~CMap()
{
	for (CEntitySpawn* spawn : availableSpawns)
	{
		spawn = nullptr;
	}
	for (CEntitySpawn* spawn : takenSpawns)
	{
		spawn = nullptr;
	}
	availableSpawns.clear();
	takenSpawns.clear();
}

CEntitySpawn* CMap::GetSpawn()
{
	CEntitySpawn* spawn = availableSpawns.front();
	availableSpawns.erase(availableSpawns.begin());
	takenSpawns.push_back(spawn);

	return spawn;
}
