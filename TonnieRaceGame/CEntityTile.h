#ifndef CENTITYTILE_H
#define CENTITYTILE_H

#include "IDrawListener.h"
#include "IInputListener.h"
#include "IBox2DListener.h"
#include "CEntity.h"
#include "CMap.h"
#include "CEngine.h"

class CEntityTile : public CEntity, public IDrawListener
{
public:
	CEntityTile(CEngine* engine, CMap* map, int spriteNumber, int tileNumber);
	void Draw(SDL_Renderer* renderer);
	void Update();

	SDL_Texture* spriteSheet;
	int xPos, yPos, textureWidth, textureHeight, textureX, textureY, tileX, tileY;
	SDL_Rect srcRect;
private:
	CEngine* engine;
};

#endif
