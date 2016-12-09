#ifndef CENTITYPOWERUP_H
#define CENTITYPOWERUP_H

#include "IDrawListener.h"
#include "IInputListener.h"
#include "IBox2DListener.h"
#include "CEntity.h"
#include "CMap.h"
#include "CEngine.h"

class CEntityPowerup : public CEntity, public IDrawListener, public IBox2DListener, public IInputListener
{
public:
	CEntityPowerup(CEngine* engine, CMap* map, double xPos, double yPos);
	bool devVisible;
	int xPos, yPos, textureWidth, textureHeight, textureX, textureY;
	double timer;
	SDL_Texture* spriteSheet;
	SDL_Rect srcRect;

	void Draw(SDL_Renderer* renderer);
	void Update();
	void Create(b2World* world);
	void CollisionBegin(CEntity* collider) override;
	void CollisionEnd(CEntity* collider) override;
	void Input(SDL_Event* event);

private:
	CEngine* engine;
};

#endif
