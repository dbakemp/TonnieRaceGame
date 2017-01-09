#ifndef CPROFILEMANAGER_H
#define CPROFILEMANAGER_H

#include "CPlayerProfile.h"

class CPlayerProfile;

class CProfileManager {
public:
	CProfileManager();
	~CProfileManager();

	bool existingProfile;

	void loadProfile();
	void saveProfile();

	bool checkLevelUnlocked(std::string mapName);

	CPlayerProfile* currentProfile;
private:
	bool checkForExistingProfile(std::string filename);
};

#endif // !CPROFILEMANAGER_H
