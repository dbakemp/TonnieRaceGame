#include "CEntityParticleEmitter.h"
#include "CDeltaHelper.h"
#include "CDrawManager.h"

CEntityParticleEmitter::CEntityParticleEmitter(CEngine* engine) : CEntity(engine), IDrawListener(engine, (int)CDrawManager::Layers::Object)
{
	this->xPos = 0;
	this->yPos = 0;
	this->engine = engine;
}

CEntityParticleEmitter::~CEntityParticleEmitter()
{
}

void CEntityParticleEmitter::Draw(SDL_Renderer* renderer)
{
}

void CEntityParticleEmitter::Update()
{
	timer += engine->deltaHelper->GetScaledDelta();

	if (timer > 0.1)
	{
		AddParticle();
		timer -= 0.1;
	}
}

void CEntityParticleEmitter::SetPosition(int x, int y)
{
	xPos = x;
	yPos = y;
}

void CEntityParticleEmitter::AddParticle()
{
	CEntitySmokeParticle* particle = new CEntitySmokeParticle(engine);
	particle->SetPosition(xPos, yPos);
	particles.push_back(particle);
}
