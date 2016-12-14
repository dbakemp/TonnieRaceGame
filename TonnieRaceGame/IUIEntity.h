#ifndef IUIEntity_H 
#define IUIEntity_H

#include "SDL.h"

class CEngine;

class IUIEntity
{
public:
	virtual void SetContainer(int x, int y, int w, int h) = 0;
};


#endif
