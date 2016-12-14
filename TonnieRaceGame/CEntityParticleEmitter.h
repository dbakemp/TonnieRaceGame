#ifndef CENTITYPARTICLEEMITTER_H
#define CENTITYPARTICLEEMITTER_H

#include "IDrawListener.h"
#include "IInputListener.h"
#include "IBox2DListener.h"
#include "CEntitySmokeParticle.h"
#include "CEntity.h"
#include "CMap.h"
#include "CEngine.h"

class CEntityParticleEmitter : public CEntity, public IDrawListener
{
public:
	CEntityParticleEmitter(CEngine* engine);
	~CEntityParticleEmitter();
	void Draw(SDL_Renderer* renderer);
	void Update();

	void SetPosition(int x, int y);

private:
	CEngine* engine;
	std::vector<CEntitySmokeParticle*> particles;
	void AddParticle();
	double timer;
};

#endif
