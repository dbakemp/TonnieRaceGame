#ifndef CENGINE_H
#define CENGINE_H

#include "SDL.h"
#include <Box2D\Box2D.h>

class CDrawManager;
class CInputManager;
class CEntityManager;
class CBox2DManager;
class CCamera;

class CEngine {
public:
	CEngine();
	CDrawManager *drawManager;
	CInputManager *inputManager;
	CEntityManager *entityManager;
	CBox2DManager *box2DManager;
	CCamera *camera;
	SDL_Window  *window;
	SDL_Renderer *renderer;
	b2World* world;
private:
	void Tick();
	int fps;
};

#endif