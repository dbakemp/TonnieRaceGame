#ifndef CENGINE_H
#define CENGINE_H

#include "SDL.h"

class CDrawManager;
class CInputManager;
class CEntityManager;

class CEngine {
public:
	CEngine();
	CDrawManager *drawManager;
	CInputManager *inputManager;
	CEntityManager *entityManager;
	SDL_Window  *window;
	SDL_Renderer *renderer;
private:
	void Tick();
};

#endif