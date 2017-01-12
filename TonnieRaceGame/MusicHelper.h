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

	void playBackgroundMusic();
	void playLastLapBackgroundMusic();

	void pauseMusic();
	void resumeMusic();

	void playTrack(std::string file, bool loop);
	void stopAll();

private:
	std::vector<HSTREAM> audioStreams;
};

#endif
