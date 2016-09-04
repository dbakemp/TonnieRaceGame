#ifndef IINPUTLISTENER_H 
#define IINPUTLISTENER_H

#include "SDL.h"

class CEngine;

class IInputListener {
public:
	virtual void Input(SDL_Event *event) = 0;
	IInputListener(CEngine *engine);
	~IInputListener();
private:
	CEngine *engine;
};


#endif
