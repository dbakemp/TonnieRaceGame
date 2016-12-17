#include "CDeltaHelper.h"

CDeltaHelper::CDeltaHelper() : timePrev(high_resolution_clock::now())
{
	this->scale = 1;
}

void CDeltaHelper::SetDelta()
{
	time_point<high_resolution_clock> timeCurrent = high_resolution_clock::now();
	duration<double> delta(timeCurrent - timePrev);
	timePrev = high_resolution_clock::now();
	this->delta = delta.count();
}

double CDeltaHelper::GetScaledDelta()
{
	return delta*scale;
}

void CDeltaHelper::SetScale(double scale)
{
	this->scale = scale;

	if(this->scale < 0)
	{
		this->scale = 0;
	}
}

double CDeltaHelper::GetScale()
{
	return scale;
}
