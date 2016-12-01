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

SDL_Texture* CAdManager::GetRandomAd(AdDirection direction)
{
	std::string index = mapIndexes[CIntegerHelper::GetRandomIntBetween(0, mapIndexes.size()-1)];
	SDL_Texture* texture = nullptr;

	switch (direction) {
		case AdDirection::DOWN:
			texture = textureMap.at(index + "-down");
			break;
		case AdDirection::UP:
			texture = textureMap.at(index + "-up");
			break;
		case AdDirection::RIGHT:
			texture = textureMap.at(index + "-right");
			break;
		case AdDirection::LEFT:
			texture = textureMap.at(index);
			break;
	}


	return texture;
}

void CAdManager::AddAd(Json::Value * ad)
{
	size_t lastindex = (*ad).get("FileName", "").asString().find_last_of(".");
	std::string rawname = (*ad).get("FileName", "").asString().substr(0, lastindex);
	std::string ext = (*ad).get("FileName", "").asString().substr(lastindex, (*ad).get("FileName", "").asString().size() - lastindex);

	std::string location = "ads/" + rawname+ ext;
	std::string locationDown = "ads/" + rawname + "-down" + ext;
	std::string locationRight = "ads/" + rawname + "-right" + ext;
	std::string locationUp = "ads/" + rawname + "-up" + ext;
	SDL_Surface* texture = IMG_Load(location.c_str());
	SDL_Surface* textureDown = IMG_Load(locationDown.c_str());
	SDL_Surface* textureRight = IMG_Load(locationRight.c_str());
	SDL_Surface* textureUp = IMG_Load(locationUp.c_str());

	textureMap.insert(std::pair<std::string, SDL_Texture*>((*ad).get("Title", "").asString(), SDL_CreateTextureFromSurface(engine->renderer, texture)));
	textureMap.insert(std::pair<std::string, SDL_Texture*>((*ad).get("Title", "").asString() + "-down", SDL_CreateTextureFromSurface(engine->renderer, textureDown)));
	textureMap.insert(std::pair<std::string, SDL_Texture*>((*ad).get("Title", "").asString() + "-right", SDL_CreateTextureFromSurface(engine->renderer, textureRight)));
	textureMap.insert(std::pair<std::string, SDL_Texture*>((*ad).get("Title", "").asString() + "-up", SDL_CreateTextureFromSurface(engine->renderer, textureUp)));

	mapIndexes.push_back((*ad).get("Title", "").asString());
}
