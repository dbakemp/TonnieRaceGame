#ifndef CENGINE_H
#define CENGINE_H

#include "SDL.h"
#include <Box2D\Box2D.h>

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
	b2World* world;
private:
	void Tick();
	int fps;
};

#endif