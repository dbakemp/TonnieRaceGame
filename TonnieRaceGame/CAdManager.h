#ifndef CADMANAGER_H
#define CADMANAGER_H
#include "SDL.h"
#include "CIntegerHelper.h"
#include "CEngine.h"
#include <Box2D\Box2D.h>
#include <vector>
#include <json\json.h>

class CAdManager
{
public:
	enum class AdDirection { UP, DOWN, LEFT, RIGHT };
	CAdManager(CEngine* engine);
	~CAdManager();
	SDL_Texture* GetRandomAd(AdDirection direction);
	void AddAd(Json::Value* ad);

	Json::Value root;
	std::map<std::string, SDL_Texture*> textureMap;
	std::vector<std::string> mapIndexes;
private:
	CEngine* engine;
};

#endif 
