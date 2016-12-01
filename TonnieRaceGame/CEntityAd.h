#ifndef CENTITYAD_H
#define CENTITYAD_H

#include "IDrawListener.h"
#include "IInputListener.h"
#include "CEntity.h"
#include "CMap.h"
#include "CEngine.h"
#include "CAdManager.h"

class CEntityAd : public CEntity, public IDrawListener
{
public:
	CEntityAd(CEngine* engine, CMap* map, CAdManager::AdDirection direction);
	void Draw(SDL_Renderer* renderer);
	void Update();

	SDL_Texture* texture;
	int xPos, yPos, textureWidth, textureHeight, textureX, textureY, tileX, tileY;
	SDL_Rect srcRect;
private:
	CEngine* engine;
};

#endif
