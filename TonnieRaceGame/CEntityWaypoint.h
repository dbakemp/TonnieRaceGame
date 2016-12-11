#ifndef CENTITYWAYPOINT_H
#define CENTITYWAYPOINT_H

#include "IDrawListener.h"
#include "IBox2DListener.h"
#include "IInputListener.h"
#include "CEntity.h"
#include "CEngine.h"
#include <json\json.h>
#include <vector>
#include <Box2D\Box2D.h>
#include <poly2tri.h>

class CEntityWaypoint : public CEntity, public IDrawListener, public IBox2DListener, public IInputListener
{
public:
	CEntityWaypoint(CEngine* engine, double x, double y, int index);
	~CEntityWaypoint();
	void Draw(SDL_Renderer* renderer);
	void Update();
	void Create(b2World* world);
	void CollisionBegin(CEntity* collider) override;
	void CollisionEnd(CEntity* collider) override;
	void Input(SDL_Event* event);
	int index;
	int radius;
private:
	CEngine* engine;
};

#endif
