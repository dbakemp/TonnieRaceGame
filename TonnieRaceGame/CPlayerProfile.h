#ifndef CPLAYERPROFILE_H
#define CPLAYERPROFILE_H

#include "CEngine.h"

#include <string>
#include <map>
#include <vector>

class CPlayerProfile {
public:
	CPlayerProfile();
	~CPlayerProfile();

	std::string name;
	std::map<std::string, bool> unlockedLevels;
	std::vector<std::string> levelProgression;

	void initializeNewProfile(std::string name);
	void unlockNextLevel(CEngine* engine);
	std::string parseToJSON();

	std::string getToUnlock(CEngine* engine);
};
#endif // !CPLAYERPROFILE_H

