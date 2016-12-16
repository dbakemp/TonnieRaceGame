#include "CSpriteSheetManager.h"

CSpriteSheetManager::CSpriteSheetManager(CEngine* engine)
{
	this->engine = engine;
}

CSpriteSheetManager::~CSpriteSheetManager()
{
	for (SSpriteSheet* spriteSheet : spriteSheets)
	{
		delete spriteSheet;
	}
	spriteSheets.clear();
}

void CSpriteSheetManager::AddSpriteSheet(SSpriteSheet* spriteSheet)
{
	spriteSheets.push_back(spriteSheet);
}

CSpriteSheetManager::SSpriteSheet* CSpriteSheetManager::GetSpriteSheetByTileId(int tileId)
{
	for (SSpriteSheet* spriteSheet : spriteSheets)
	{
		if (tileId >= spriteSheet->minTileIndex && spriteSheet->maxTileIndex >= tileId)
		{
			return spriteSheet;
		}
	}

	return nullptr;
}
