#include "CEntitySmokeParticle.h"
#include "CDrawManager.h"
#include "CTextureManager.h"
#include "CCamera.h"
#include "CDeltaHelper.h"
#include "CCameraManager.h"

CEntitySmokeParticle::CEntitySmokeParticle(CEngine* engine) : CEntity(engine), IDrawListener(engine, ((int)CDrawManager::Layers::Object) - 1)
{
	this->texture = engine->textureManager->GetTexture("Images/smokeGrey0.png");
	SDL_QueryTexture(this->texture, NULL, NULL, &srcrect.w, &srcrect.h);
	this->srcrect.w /= 4;
	this->srcrect.h /= 4;
	this->srcrect.x = srcrect.w / 2;
	this->srcrect.y = srcrect.h / 2;
	this->angle = 0;
	this->angulatVelocity = 0.3;
	this->engine = engine;
}

CEntitySmokeParticle::~CEntitySmokeParticle()
{
}

void CEntitySmokeParticle::Draw(SDL_Renderer* renderer)
{
	dstrect = { (int)xPos - engine->cameraManager->GetCurrentCamera()->GetXPos(), (int)yPos - engine->cameraManager->GetCurrentCamera()->GetYPos(), srcrect.w, srcrect.h };
	SDL_Point center = {srcrect.x, srcrect.y};
	SDL_RenderCopyEx(renderer, texture, NULL, &dstrect, angle, &center, SDL_FLIP_NONE);
}

void CEntitySmokeParticle::Update()
{
	angle += angulatVelocity;

	timer += engine->deltaHelper->GetScaledDelta();

	if (timer > 0.3)
	{
		shouldDelete = true;
	}
}

void CEntitySmokeParticle::SetPosition(int x, int y)
{
	xPos = x;
	yPos = y;
}
