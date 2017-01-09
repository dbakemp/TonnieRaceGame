#include "CTimerHelper.h"

CTimerHelper::CTimerHelper()
{
	this->running = false;
}

void CTimerHelper::Start()
{
	running = true;
	startTime = clock();
	currentTime = startTime;
}

void CTimerHelper::Stop()
{
	running = false;
}

std::string CTimerHelper::Lap()
{
	int milliseconds = currentTime - startTime;
	int minutes = milliseconds / 60000;
	int seconds = (milliseconds % 60000) / 1000;
	int milli = ((milliseconds % 60000) % 1000);
	std::string minutesString = std::to_string(minutes);
	std::string secondsString = std::to_string(seconds);
	std::string milliString = std::to_string(milli);

	return std::string(2 - minutesString.length(), '0')+ minutesString +":"+ std::string(2 - secondsString.length(), '0') + secondsString+","+std::string(3 - milliString.length(), '0') + milliString;
}

int CTimerHelper::LapAsInt()
{
	return currentTime - startTime;
}

void CTimerHelper::Update()
{
	if (running) {
		currentTime = clock();
	}
}
