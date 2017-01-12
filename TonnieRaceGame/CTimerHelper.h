#ifndef CTIMERHELPER_H
#define CTIMERHELPER_H

#include <string>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <ctime>

class CTimerHelper
{
public:
	CTimerHelper();
	void Start();
	void Stop();
	std::string Lap();
	int LapAsInt();
	std::string IntToString(int timestamp);
	void Update();
	void Pause();
	void Resume();
private:

	bool running;
	int startTime;
	int currentTime;
	int pauseTime;
	int pauseBias;
	bool paused;
};

#endif /* CIntegerHelper_hpp */
