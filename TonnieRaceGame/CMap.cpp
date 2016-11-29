#include "CMap.h"

CMap::CMap()
{
}

CMap::~CMap()
{
}

CEntitySpawn* CMap::GetSpawn()
{
	CEntitySpawn* spawn = availableSpawns.front();
	availableSpawns.erase(availableSpawns.begin());
	takenSpawns.push_back(spawn);

	return spawn;
}
