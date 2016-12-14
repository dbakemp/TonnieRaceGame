#ifndef CENTITYSPAWN_H
#define CENTITYSPAWN_H

#include "IDrawListener.h"
#include "IBox2DListener.h"
#include "IInputListener.h"
#include "CEntity.h"
#include "CEngine.h"
#include <json\json.h>
#include <vector>
#include <Box2D\Box2D.h>
#include <poly2tri.h>

class CEntitySpawn : public CEntity
{
public:
	CEntitySpawn(CEngine* engine, int x, int y);
	~CEntitySpawn();
	void Update();
	int x, y;
private:
	CEngine* engine;
};

#endif
