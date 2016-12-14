#include "CEntitySpawn.h"

CEntitySpawn::CEntitySpawn(CEngine * engine, int x, int y) : CEntity(engine)
{
	this->x = x;
	this->y = y;
	this->engine = engine;
}

CEntitySpawn::~CEntitySpawn()
{
}

void CEntitySpawn::Update()
{
}
