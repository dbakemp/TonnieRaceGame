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
	void Update();
private:

	bool running;
	int startTime;
	int currentTime;
};

#endif /* CIntegerHelper_hpp */
