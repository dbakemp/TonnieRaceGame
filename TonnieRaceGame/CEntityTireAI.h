#ifndef CENTITYTIREAI_H
#define CENTITYTIREAI_H

#include "IDrawListener.h"
#include "IInputListener.h"
#include "IBox2DListener.h"
#include "CEntity.h"
#include "CEngine.h"
#include <Box2D\Box2D.h>

class CMap;

class CEntityTireAI : public CEntity, public IDrawListener,  public IBox2DListener
{
public:
	CEntityTireAI(CEngine* engine, CMap* map, int x, int y);
	void Draw(SDL_Renderer* renderer);
	void Update();
	void Create(b2World* world);

	void UpdateFriction();
	void UpdateDrive();
	void UpdateTurn();

	b2Vec2 GetLateralVelocity();
	b2Vec2 GetForwardVelocity();

	float maxForwardSpeed;
	float maxBackwardsSpeed;
	float maxDriveForce;
private:
	CEngine* engine;
};

#endif