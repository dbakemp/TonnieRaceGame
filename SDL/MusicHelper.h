#ifndef MUSICHELPER_H
#define MUSICHELPER_H

#include "Bass.h"
#include <iostream>
#include <string>
#include <vector>

class MusicHelper
{
public:
	MusicHelper();
	~MusicHelper();

	void playBackgroundMusic(std::string file);
	void playSingleTrack(std::string file);

private:
	std::vector<HSTREAM> audioStreams;
};

#endif