#ifndef CFONTMANAGER_H
#define CFONTMANAGER_H
#include "SDL.h"
#include "CIntegerHelper.h"
#include "CEngine.h"
#include "SDL_ttf.h"
#include <map>

class CFontManager
{
public:
	CFontManager(CEngine* engine);
	~CFontManager();
	TTF_Font* AddFont(std::string fontName, int size);
	TTF_Font* GetFont(std::string fontName, int size);
private:
	std::map<std::string, TTF_Font*> fontMap;
	CEngine* engine;
};

#endif 
