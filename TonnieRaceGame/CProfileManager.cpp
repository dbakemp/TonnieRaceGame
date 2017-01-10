#include "CProfileManager.h"
#include "CDebugLogger.h"
#include <iostream>
#include <fstream>

#include <json/json.h>

CProfileManager::CProfileManager() {
	existingProfile = true;

	if (existingProfile) loadProfile();
	//existingProfile = checkForExistingProfile("profile.txt");

	//CDebugLogger::PrintDebug(currentProfile->name);
}

CProfileManager::~CProfileManager() {
	delete currentProfile;
	existingProfile = nullptr;
}

void CProfileManager::loadProfile() {
	std::ifstream profileFile;
	profileFile.open("profile.txt");

	if (profileFile.is_open()) {
		currentProfile = new CPlayerProfile();
		Json::Value profileJson;
		Json::Reader reader;

		if (reader.parse(profileFile, profileJson, false))
		{
			currentProfile->name = profileJson["profile"]["name"].asString();
			for (Json::Value map : profileJson["profile"]["unlockedMaps"])
			{
				currentProfile->unlockedLevels.insert(std::pair<std::string, bool>(map.get("name", "").asString(), map.get("unlocked", "").asBool()));
			}
		}
	}
}

void CProfileManager::saveProfile() {
	std::ofstream profileFile;
	profileFile.open("profile.txt", std::ofstream::out | std::ofstream::trunc);

	if (profileFile.is_open()) {
		profileFile << currentProfile->parseToJSON();
	}
	else {
		CDebugLogger::PrintDebug("Profiel bestand kon niet worden geopend!");
	}
}

bool CProfileManager::checkLevelUnlocked(std::string mapName) {
	bool unlocked = false;

	for (std::pair<std::string, bool> map : currentProfile->unlockedLevels) {
		if (map.first == mapName) {
			unlocked = map.second;
		}
	}

	return unlocked;
}

bool CProfileManager::checkForExistingProfile(std::string filename) {
	struct stat buffer;
	return (stat(filename.c_str(), &buffer) == 0);
}