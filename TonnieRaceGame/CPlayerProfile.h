#ifndef CPLAYERPROFILE_H
#define CPLAYERPROFILE_H

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
	void unlockNextLevel();
	std::string parseToJSON();

	std::string getToUnlock();
};
#endif // !CPLAYERPROFILE_H

