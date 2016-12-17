#ifndef CDELTAHELPER_H
#define CDELTAHELPER_H

#include <chrono>

using namespace std::chrono;

class CDeltaHelper
{
public:
	CDeltaHelper();
	void SetDelta();
	double delta;
	double GetScaledDelta();
	void SetScale(double scale);
	double GetScale();
private:
	time_point<high_resolution_clock> timePrev;
	double scale;
};

#endif
