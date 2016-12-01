#include "CAdManager.h"
#include "SDL_image.h"
#include <iostream>
#include <fstream>

CAdManager::CAdManager(CEngine* engine)
{
	this->engine = engine;

	Json::Reader reader;

	std::ifstream stream("ads/ad.json", std::ifstream::binary);
	if (reader.parse(stream, root, false))
	{
		for (Json::Value ad : root["Ads"])
		{
			AddAd(&ad);
		}
	}
}

SDL_Texture* CAdManager::GetRandomAd()
{
	std::string index = mapIndexes[CIntegerHelper::GetRandomIntBetween(0, mapIndexes.size()-1)];
	return textureMap.at(index);
}

void CAdManager::AddAd(Json::Value * ad)
{
	std::string location = "ads/" + (*ad).get("FileName", "").asString();
	SDL_Surface* texture = IMG_Load(location.c_str());
	SDL_Texture *text = IMG_LoadTexture(engine->renderer, location.c_str());

	float angle = 180.0f; // set the angle.
	SDL_Point center = { 8, 8 }; // the center where the texture will be rotated.
	SDL_RendererFlip flip = SDL_FLIP_NONE; // the flip of the texture.

										   // now, try to draw something
	SDL_RenderCopyEx(engine->renderer, text, NULL, NULL, angle, &center, flip);
	std::cout << "flipie";
	texture = (SDL_Surface*)text;

	textureMap.insert(std::pair<std::string, SDL_Texture*>((*ad).get("Title", "").asString(), SDL_CreateTextureFromSurface(engine->renderer, texture)));
	mapIndexes.push_back((*ad).get("Title", "").asString());
}
