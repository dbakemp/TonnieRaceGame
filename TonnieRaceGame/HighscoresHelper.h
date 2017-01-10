#pragma once
#include <string>
#include "CUILabel.h"
class HighscoresHelper
{
public:
	HighscoresHelper();
	void getHighscore(int level);
	void addHighScore(std::string name, std::string score, int level);
	std::vector<CUILabel*> processJSON();
	~HighscoresHelper();
};
