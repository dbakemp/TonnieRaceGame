#pragma once
#include <string>

class HighscoresHelper
{
public:
	HighscoresHelper();
	void getHighscore(int level);
	void addHighScore(std::string name, std::string score, int level);
	~HighscoresHelper();
};
