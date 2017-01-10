#include "CPlayerProfile.h"
#include "CDebugLogger.h"

#include <fstream>
#include <json/json.h>

CPlayerProfile::CPlayerProfile() {

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
			this->unlockedLevels.insert(std::pair<std::string, bool>(map.get("mapname", "").toStyledString(), false));
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

	Json::FastWriter writer;
	std::string returnString = writer.write(profileJson);
	return returnString;
}
