#ifndef CPLAYERPROFILE_H
#define CPLAYERPROFILE_H

#include <string>
#include <map>

class CPlayerProfile {
public:
	CPlayerProfile();
	~CPlayerProfile();

	std::string name;
	std::map<std::string, bool> unlockedLevels;

	void initializeNewProfile(std::string name);
	std::string parseToJSON();
};
#endif // !CPLAYERPROFILE_H

