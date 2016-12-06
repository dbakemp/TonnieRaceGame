#ifndef CENTITYTILE_H
#define CENTITYTILE_H

#include "IDrawListener.h"
#include "IInputListener.h"
#include "IBox2DListener.h"
#include "CSpriteSheetManager.h"
#include "CEntity.h"
#include "CMap.h"
#include "CEngine.h"

class CEntityTile : public CEntity, public IDrawListener
{
public:
	CEntityTile(CEngine* engine, CSpriteSheetManager::SSpriteSheet* spriteSheet, int spriteNumber, int tileNumber, int mapWidth, int mapHeight, int mapTileWidth, int mapTileHeight);
	void Draw(SDL_Renderer* renderer);
	void Update();

	CSpriteSheetManager::SSpriteSheet* spriteSheet;

	int xPos, yPos, textureWidth, textureHeight, textureX, textureY, tileX, tileY;
	SDL_Rect srcRect;
private:
	CEngine* engine;
};

#endif
