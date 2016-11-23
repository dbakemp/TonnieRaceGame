#include "CEntityTile.h"
#include "CCamera.h"

CEntityTile::CEntityTile(CEngine* engine, CMap* map, int spriteNumber, int tileNumber) : CEntity(engine), IDrawListener(engine)
{
	this->engine = engine;

	int count = map->spriteSheetWidth / (map->spriteSheetTileWidth + map->spriteSheetSpacing);
	int rowNumber = (spriteNumber / count);
	int columnsNumber = (spriteNumber % count) - 1;

	this->tileY = tileNumber / map->width;
	this->tileX = tileNumber % map->width;

	this->textureX = columnsNumber * (map->spriteSheetTileWidth + map->spriteSheetSpacing);
	this->textureY = rowNumber * (map->spriteSheetTileHeight + map->spriteSheetSpacing);
	this->spriteSheet = map->spriteSheet;
	this->textureHeight = map->spriteSheetTileHeight;
	this->textureWidth = map->spriteSheetTileWidth;

	srcRect = {this->textureX, this->textureY, this->textureWidth, this->textureHeight};
}

void CEntityTile::Draw(SDL_Renderer* renderer)
{
	SDL_Rect dstrect = {-engine->camera->posX + (tileX * this->textureWidth), -engine->camera->posY + (tileY * this->textureHeight), this->textureWidth, this->textureHeight};
	SDL_RenderCopy(engine->renderer, spriteSheet, &srcRect, &dstrect);
}

void CEntityTile::Update()
{
}
