#include "CDeltaHelper.h"

CDeltaHelper::CDeltaHelper() : timePrev(high_resolution_clock::now())
{
}

void CDeltaHelper::SetDelta()
{
	time_point<high_resolution_clock> timeCurrent = high_resolution_clock::now();
	duration<double> delta(timeCurrent - timePrev);
	timePrev = high_resolution_clock::now();
	this->delta = delta.count();
}
