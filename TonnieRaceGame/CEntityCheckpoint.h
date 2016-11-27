#ifndef CENTITYCHECKPOINT_H
#define CENTITYCHECKPOINT_H

#include "IDrawListener.h"
#include "IBox2DListener.h"
#include "IInputListener.h"
#include "CEntity.h"
#include "CEngine.h"
#include <json\json.h>
#include <vector>
#include <Box2D\Box2D.h>
#include <poly2tri.h>

class CEntityCheckpoint : public CEntity, public IDrawListener, public IBox2DListener, public IInputListener
{
public:
	CEntityCheckpoint(CEngine* engine, b2Vec2* start, b2Vec2* end, int index);
	void Draw(SDL_Renderer* renderer);
	void Update();
	void Create(b2World* world);
	void CollisionBegin(CEntity* collider) override;
	void CollisionEnd(CEntity* collider) override;
	void Input(SDL_Event* event);
	int checkpointIndex;
private:
	CEngine* engine;
};

#endif
