#ifndef CENTITYSPEEDOMETER_H
#define CENTITYSPEEDOMETER_H

#include "CCamera.h"
#include "CEngine.h"
#include "IBox2DListener.h"

class CEntitySpeedoMeter
{
public:
	void SetChild(IBox2DListener* child);
	IBox2DListener* GetChild();

private:
	IBox2DListener* child;
};

#endif 
