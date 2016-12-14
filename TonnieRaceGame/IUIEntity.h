#ifndef IUIEntity_H 
#define IUIEntity_H

#include "SDL.h"

class CEngine;

class IUIEntity
{
public:
	virtual void SetContainer(int x, int y, int w, int h) = 0;
	virtual void SetPosition(int x, int y) = 0;
	virtual void SetTag(std::string tag) = 0;
	virtual std::string GetTag() = 0;

	SDL_Rect UIdstrect;
	int UIXPos;
	int UIYPos;
	std::string tag;
};


#endif
