#ifndef CCAMERA_H
#define CCAMERA_H

#include "CCamera.h"
#include "CEngine.h"
#include "IBox2DListener.h"

class CCamera
{
public:
	CCamera(CEngine* engine);
	void Update();
	void SetChild(IBox2DListener* child);
	IBox2DListener* GetChild();
	int posX, posY;
	int windowHeight, windowWidth;
private:
	IBox2DListener* child; 
	CEngine* engine;
};

#endif 
