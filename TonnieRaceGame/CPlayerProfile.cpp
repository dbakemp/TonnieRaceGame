#include "CPlayerProfile.h"
#include "CDebugLogger.h"

#include  "CEngine.h"

#include <string>
#include <fstream>
#include <json/json.h>

CPlayerProfile::CPlayerProfile() {
	Json::Value root;
	Json::Reader reader;

	std::ifstream stream("Resources/Maps/maps.json", std::ifstream::binary);
	if (reader.parse(stream, root, false))
	{
		for (Json::Value map : root["maps"])
		{
			levelProgression.push_back(map.get("mapname", "").asString());
		}
	}
}

CPlayerProfile::~CPlayerProfile() {

}

void CPlayerProfile::initializeNewProfile(std::string name) {
	this->name = name;

	Json::Value root;
	Json::Reader reader;

	std::ifstream stream("Resources/Maps/maps.json", std::ifstream::binary);
	if (reader.parse(stream, root, false))
	{
		for (Json::Value map : root["maps"])
		{
			if (map.get("startmap", "").asBool()) this->unlockedLevels.insert(std::pair<std::string, bool>(map.get("mapname", "").asString(), true));
			else this->unlockedLevels.insert(std::pair<std::string, bool>(map.get("mapname", "").asString(), false));
		}
	}

	//CDebugLogger::PrintDebug("KLAAR");
}

std::string CPlayerProfile::parseToJSON() {
	Json::Value profileJson;

	profileJson["profile"]["name"] = this->name;

	Json::Value vec(Json::arrayValue);

	for (std::pair<std::string, bool> map : this->unlockedLevels) {
		Json::Value record;
		record["name"] = map.first;
		record["unlocked"] = map.second;
		vec.append(record);
	}

	profileJson["profile"]["unlockedMaps"] = vec;

	Json::StyledWriter writer;
	std::string returnString = writer.write(profileJson);
	return returnString;
}

void CPlayerProfile::unlockNextLevel(CEngine* engine) {
	unlockedLevels.at(getToUnlock(engine)) = true;
}

std::string CPlayerProfile::getToUnlock(CEngine* engine) {
	std::string temp;

	for (int i = 0; i < levelProgression.size(); i++) {
		if (levelProgression.at(i) == engine->level) {
			temp = levelProgression.at(i + 1);
		}
	}

	/*
	for (int i = 0; i < levelProgression.size(); i++) {
	if (unlockedLevels.at(levelProgression.at(i)) == true && levelProgression.at(i) != levelProgression.back()) {
	temp = levelProgression.at(i + 1);
	}
	}
	*/

	

	return temp;
}
