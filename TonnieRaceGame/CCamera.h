#ifndef CCAMERA_H
#define CCAMERA_H

#include "CEngine.h"
#include "IBox2DListener.h"

class CCamera
{
public:
	CCamera(CEngine* engine);
	void Update();
	void SetChild(IBox2DListener* child);
	IBox2DListener* GetChild();
	int GetXPos();
	int GetYPos();
private:
	IBox2DListener* child;
	CEngine* engine;
	int posX, posY;
};

#endif
