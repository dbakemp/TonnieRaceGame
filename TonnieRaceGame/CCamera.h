#ifndef CCAMERA_H
#define CCAMERA_H

#include "CEngine.h"
#include "IBox2DListener.h"
#include "SDL.h"

class CCamera
{
public:
	CCamera(CEngine* engine);
	void Update();
	void SetChild(IBox2DListener* child);
	IBox2DListener* GetChild();
	int GetXPos();
	int GetYPos();
	void SetViewPort(int w, int h, int x, int y);
	SDL_Rect GetViewPort();
private:
	IBox2DListener* child;
	CEngine* engine;
	int posX, posY;
	SDL_Rect viewport;
};

#endif
