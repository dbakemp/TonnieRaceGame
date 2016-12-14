#ifndef CSPRITESHEETMANAGER_H
#define CSPRITESHEETMANAGER_H
#include "SDL.h"
#include "CIntegerHelper.h"
#include "CEngine.h"
#include "SDL_image.h"
#include <Box2D\Box2D.h>
#include <vector>
#include <json\json.h>

class CSpriteSheetManager
{
public:
	struct SSpriteSheet {
		int columns;
		int spacing;
		int width;
		int height;
		int tileWidth;
		int tileHeight;
		int minTileIndex;
		int maxTileIndex;
		SDL_Texture* texture;
	};

	CSpriteSheetManager(CEngine* engine);
	~CSpriteSheetManager();
	void AddSpriteSheet(SSpriteSheet* spriteSheet);
	SSpriteSheet* GetSpriteSheetByTileId(int tileId);
	std::vector<SSpriteSheet*> spriteSheets;
private:
	CEngine* engine;
};

#endif 
