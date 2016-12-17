#include "CEntityTile.h"
#include "CCamera.h"
#include "CDrawManager.h"
#include "CCameraManager.h"

CEntityTile::CEntityTile(CEngine* engine, CSpriteSheetManager::SSpriteSheet* spriteSheet, int spriteNumber, int tileNumber, int mapWidth, int mapHeight, int mapTileWidth, int mapTileHeight) : CEntity(engine), IDrawListener(engine, (int)CDrawManager::Layers::Tile)
{
	this->engine = engine;

	int count = spriteSheet->width / (spriteSheet->tileWidth + spriteSheet->spacing);
	int rowNumber = (spriteNumber / count);
	int columnsNumber = (spriteNumber % count) - 1;

	int tileNumberRest = tileNumber % mapWidth;

	int yRest = spriteSheet->tileHeight - mapTileHeight;

	this->tileY = (((tileNumber - tileNumberRest) / mapWidth) * mapTileHeight) - yRest;
	this->tileX = tileNumberRest * mapTileWidth;

	this->textureX = 0;
	this->textureY = 0;
	if (spriteSheet->columns != 0)
	{
		this->textureX = columnsNumber * (spriteSheet->tileWidth + spriteSheet->spacing);
		this->textureY = rowNumber * (spriteSheet->tileHeight + spriteSheet->spacing);
	}
	this->textureHeight = spriteSheet->tileHeight;
	this->textureWidth = spriteSheet->tileWidth;

	this->spriteSheet = spriteSheet;

	srcRect = {this->textureX, this->textureY, this->textureWidth, this->textureHeight};
}

CEntityTile::~CEntityTile()
{
}

void CEntityTile::Draw(SDL_Renderer* renderer)
{
	SDL_Rect dstrect = {-engine->cameraManager->GetCurrentCamera()->GetXPos() + tileX, -engine->cameraManager->GetCurrentCamera()->GetYPos() + tileY, this->textureWidth, this->textureHeight};
	SDL_RenderCopy(renderer, spriteSheet->texture, &srcRect, &dstrect);
}

void CEntityTile::Update()
{
}
