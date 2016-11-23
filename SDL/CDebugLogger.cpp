#include "CDebugLogger.h"
#include <chrono>
#include <iomanip>

void CDebugLogger::PrintDebug(std::string log)
{
	tm localTime;
	std::chrono::system_clock::time_point t = std::chrono::system_clock::now();
	time_t now = std::chrono::system_clock::to_time_t(t);
	localtime_s(&localTime, &now);

	const std::chrono::duration<double> tse = t.time_since_epoch();
	std::chrono::seconds::rep milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(tse).count() % 1000;

	std::cout << "["
		<< std::setfill('0') << std::setw(2) << localTime.tm_hour << ':'
		<< std::setfill('0') << std::setw(2) << localTime.tm_min << ':'
		<< std::setfill('0') << std::setw(2) << localTime.tm_sec << '.'
		<< std::setfill('0') << std::setw(3) << milliseconds << "] "
		<< log
		<< std::endl;
}
