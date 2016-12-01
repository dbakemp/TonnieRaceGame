#include "CEntityAd.h"
#include "CDrawManager.h"
#include "CAdManager.h"
#include "CCamera.h"

CEntityAd::CEntityAd(CEngine * engine, CMap * map) : CEntity(engine), IDrawListener(engine, ((int)CDrawManager::Layers::Tile)+1)
{
	texture = engine->adManager->GetRandomAd();

	this->engine = engine;
}

void CEntityAd::Draw(SDL_Renderer * renderer)
{
	SDL_Rect dstrect = { -engine->camera->posX + tileX, -engine->camera->posY + tileY, this->textureWidth, this->textureHeight };
	SDL_RenderCopy(engine->renderer, texture, NULL, &dstrect);
}

void CEntityAd::Update()
{
}
