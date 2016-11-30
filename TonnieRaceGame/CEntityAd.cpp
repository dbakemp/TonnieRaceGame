#include "CEntityAd.h"
#include "CDrawManager.h"
#include "CAdManager.h"
#include "CCamera.h"

CEntityAd::CEntityAd(CEngine * engine, CMap * map) : CEntity(engine), IDrawListener(engine, (int)CDrawManager::Layers::Tile)
{
	texture = engine->adManager->GetRandomAd();

	this->engine = engine;
}

void CEntityAd::Draw(SDL_Renderer * renderer)
{
	if ((tileY * this->textureHeight) > engine->camera->posY - this->textureHeight && (tileX * this->textureWidth) > engine->camera->posX - this->textureWidth && (tileY * this->textureHeight) < engine->camera->posY + engine->windowHeight && (tileX * this->textureWidth) < engine->camera->posX + engine->windowWidth)
	{
		SDL_Rect dstrect = { -engine->camera->posX + (tileX * this->textureWidth), -engine->camera->posY + (tileY * this->textureHeight), this->textureWidth, this->textureHeight };
		SDL_RenderCopy(engine->renderer, texture, &srcRect, &dstrect);
	}
}

void CEntityAd::Update()
{
}
