#ifndef IENTITYLISTENER_H 
#define IENTITYLISTENER_H

#include "SDL.h"

class CEngine;

class IEntityListener
{
public:
	virtual void Update() = 0;
	IEntityListener(CEngine* engine);
	~IEntityListener();
private:
	CEngine* engine;
};


#endif
