#pragma once

#include <string>

class AdHelper
{
public:
	AdHelper();
	void processJSON();
	void fetchJSON();
	void fetchAd(std::string title, std::string url, std::string filename);
	~AdHelper();
};

