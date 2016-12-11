#include "CEntityAd.h"
#include "CDrawManager.h"
#include "CAdManager.h"
#include "CCamera.h"

CEntityAd::CEntityAd(CEngine * engine, CMap * map, CAdManager::AdDirection direction) : CEntity(engine), IDrawListener(engine, ((int)CDrawManager::Layers::Tile)+1)
{
	texture = engine->adManager->GetRandomAd(direction);

	this->engine = engine;
}

CEntityAd::~CEntityAd()
{
}

void CEntityAd::Draw(SDL_Renderer * renderer)
{
	SDL_Rect dstrect = { -engine->camera->posX + tileX, -engine->camera->posY + tileY, this->textureWidth, this->textureHeight };
	SDL_RenderCopy(engine->renderer, texture, NULL, &dstrect);
}

void CEntityAd::Update()
{
}
