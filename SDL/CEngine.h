#ifndef CENGINE_H
#define CENGINE_H

#include "SDL.h"

class CDrawManager;
class CInputManager;
class CEntityManager;
class CCamera;

class CEngine {
public:
	CEngine();
	CDrawManager *drawManager;
	CInputManager *inputManager;
	CEntityManager *entityManager;
	CCamera *camera;
	SDL_Window  *window;
	SDL_Renderer *renderer;
private:
	void Tick();
};

#endif