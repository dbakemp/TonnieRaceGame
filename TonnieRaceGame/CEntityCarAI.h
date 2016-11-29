#ifndef CENTITYCARAI_H
#define CENTITYCARAI_H

#include "IDrawListener.h"
#include "IInputListener.h"
#include "IBox2DListener.h"
#include "ILapCountable.h"
#include "CEngine.h"
#include "CEntity.h"
#include "CEntityTireAI.h"
#include "CEntityWaypoint.h"
#include "CEntityCheckpoint.h"
#include <vector>
#include <Box2D\Box2D.h>

class CMap;

class CEntityCarAI : public CEntity, public IDrawListener, public IBox2DListener, public ILapCountable
{
public:
	CEntityCarAI(CEngine* engine, CMap* map);
	void Draw(SDL_Renderer* renderer);
	void Update();
	void Create(b2World* world);
	b2RevoluteJoint *flJoint, *frJoint;
	std::vector<CEntityTireAI*> tires;
	void CollisionBegin(CEntity* collider) override;
	void CollisionEnd(CEntity* collider) override;
	void ProcessCheckpoint(CEntityCheckpoint* checkpoint);
	void ProcessWaypoint(CEntityWaypoint* waypoint);

	int currentWaypoint;
	CEntityWaypoint* heading;

	SDL_Texture* spriteSheet;
	SDL_Rect srcRect;
private:
	CEngine* engine;
};

#endif
