#ifndef CTEXTUREMANAGER_H
#define CTEXTUREMANAGER_H
#include "SDL.h"
#include "CIntegerHelper.h"
#include "CEngine.h"
#include "SDL_ttf.h"
#include <map>

class CTextureManager
{
public:
	CTextureManager(CEngine* engine);
	~CTextureManager();
	SDL_Texture* AddTexture(std::string textureName);
	SDL_Texture* GetTexture(std::string textureName);
private:
	std::map<std::string, SDL_Texture*> textureMap;
	CEngine* engine;
};

#endif 
