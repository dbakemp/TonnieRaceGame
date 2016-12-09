#include "CFontManager.h"
#include <algorithm>
#include <string> 

CFontManager::CFontManager(CEngine* engine)
{
	TTF_Init();
	this->engine = engine;
}

CFontManager::~CFontManager()
{
	TTF_Quit();
}

TTF_Font* CFontManager::AddFont(std::string fontName, int size)
{
	std::string fontLocation = "Resources/Fonts/" + fontName + ".ttf";
	TTF_Font* font = TTF_OpenFont(fontLocation.c_str(), size);
	TTF_SetFontHinting(font, TTF_HINTING_MONO);

	fontMap.insert(std::pair<std::string, TTF_Font*>(fontName+std::to_string(size), font));
	return font;
}

TTF_Font* CFontManager::GetFont(std::string fontName, int size)
{
	std::transform(fontName.begin(), fontName.end(), fontName.begin(), ::tolower);
	TTF_Font* font;

	if (fontMap.find(fontName + std::to_string(size)) == fontMap.end()) {
		font = AddFont(fontName, size);
	}
	else {
		font = fontMap.at(fontName + std::to_string(size));
	}

	return font;
}
