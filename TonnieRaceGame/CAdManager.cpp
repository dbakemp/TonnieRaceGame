#include "CAdManager.h"
#include "SDL_image.h"
#include "CTextureManager.h"
#include <iostream>
#include <fstream>

CAdManager::CAdManager(CEngine* engine)
{
	this->engine = engine;

	Json::Reader reader;

	std::ifstream stream("Resources/Ads/ad.json", std::ifstream::binary);
	if (reader.parse(stream, root, false))
	{
		for (Json::Value ad : root["Ads"])
		{
			AddAd(&ad);
		}
	}
}

CAdManager::~CAdManager()
{
	for (std::pair<std::string, SDL_Texture*> pair : textureMap) {
		pair.second = nullptr;
	}
	textureMap.clear();
	mapIndexes.clear();
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
	if ((*ad).get("IsActive", "").asString() == "1")
	{
		size_t lastindex = (*ad).get("FileName", "").asString().find_last_of(".");
		std::string rawname = (*ad).get("FileName", "").asString().substr(0, lastindex);
		std::string ext = (*ad).get("FileName", "").asString().substr(lastindex, (*ad).get("FileName", "").asString().size() - lastindex);

		std::string location = "Ads/" + rawname + ext;
		std::string locationDown = "Ads/" + rawname + "-down" + ext;
		std::string locationRight = "Ads/" + rawname + "-right" + ext;
		std::string locationUp = "Ads/" + rawname + "-up" + ext;

		textureMap.insert(std::pair<std::string, SDL_Texture*>((*ad).get("Title", "").asString(), engine->textureManager->GetTexture(location)));
		textureMap.insert(std::pair<std::string, SDL_Texture*>((*ad).get("Title", "").asString() + "-down", engine->textureManager->GetTexture(locationDown)));
		textureMap.insert(std::pair<std::string, SDL_Texture*>((*ad).get("Title", "").asString() + "-right", engine->textureManager->GetTexture(locationRight)));
		textureMap.insert(std::pair<std::string, SDL_Texture*>((*ad).get("Title", "").asString() + "-up", engine->textureManager->GetTexture(locationUp)));

		mapIndexes.push_back((*ad).get("Title", "").asString());
	}
}
