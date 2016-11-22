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

	void playTrack(std::string file, bool loop);

private:
	std::vector<HSTREAM> audioStreams;
};

#endif