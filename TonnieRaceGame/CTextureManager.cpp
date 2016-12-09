#include "CTextureManager.h"
#include "SDL_image.h"

CTextureManager::CTextureManager(CEngine * engine)
{
	this->engine = engine;
}

CTextureManager::~CTextureManager()
{
}

SDL_Texture * CTextureManager::AddTexture(std::string textureName)
{
	std::string textureLocation = "Resources/" + textureName;


	SDL_Surface* surface = IMG_Load(textureLocation.c_str());
	SDL_Texture* texture = SDL_CreateTextureFromSurface(engine->renderer, surface);
	SDL_FreeSurface(surface);

	textureMap.insert(std::pair<std::string, SDL_Texture*>(textureName, texture));

	return texture;
}

SDL_Texture* CTextureManager::GetTexture(std::string textureName)
{
	SDL_Texture* texture;

	if (textureMap.find(textureName) == textureMap.end()) {
		texture = AddTexture(textureName);
	}
	else {
		texture = textureMap.at(textureName);
	}

	return texture;
}
