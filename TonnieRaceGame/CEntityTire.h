#ifndef CENTITYTIRE_H
#define CENTITYTIRE_H

#include "IDrawListener.h"
#include "IInputListener.h"
#include "IBox2DListener.h"
#include "CEntity.h"
#include "CEngine.h"
#include <Box2D\Box2D.h>

class CMap;

class CEntityTire : public CEntity, public IDrawListener, public IInputListener, public IBox2DListener
{
public:
	CEntityTire(CEngine* engine, CMap* map, int x, int y);
	void Draw(SDL_Renderer* renderer);
	void Input(SDL_Event* event);
	void Update();
	void Create(b2World* world);

	void UpdateFriction();
	void UpdateDrive();
	void UpdateTurn();
	void OnControllerButton(const SDL_ControllerButtonEvent sdlEvent);

	b2Vec2 GetLateralVelocity();
	b2Vec2 GetForwardVelocity();

	float maxForwardSpeed;
	float maxBackwardsSpeed;
	float maxDriveForce;
private:
	CEngine* engine;
};

#endif
