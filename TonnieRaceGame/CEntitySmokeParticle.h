#ifndef CENTITYSMOKEPARTICLE_H
#define CENTITYSMOKEPARTICLE_H

#include "IDrawListener.h"
#include "IInputListener.h"
#include "IBox2DListener.h"
#include "CEntity.h"
#include "CMap.h"
#include "CEngine.h"

class CEntitySmokeParticle : public CEntity, public IDrawListener
{
public:
	CEntitySmokeParticle(CEngine* engine);
	~CEntitySmokeParticle();

	void Draw(SDL_Renderer* renderer);
	void Update();

	void SetPosition(int x, int y);

private:
	CEngine* engine;
	float angle;
	float angulatVelocity;
	double timer;
};

#endif
