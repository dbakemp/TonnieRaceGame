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
	SDL_Renderer *renderer;
private:
	void Tick();
};

#endif