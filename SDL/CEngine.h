#ifndef CENGINE_H
#define CENGINE_H

#include "SDL.h"

class CDrawManager;
class CInputManager;

class CEngine {
public:
	CEngine();
	CDrawManager *drawManager;
	CInputManager *inputManager;
	SDL_Window  *window;
private:
	void Tick();
};

#endif