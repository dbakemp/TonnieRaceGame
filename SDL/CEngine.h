#ifndef CENGINE_H
#define CENGINE_H

#include "SDL.h"
#include "MusicHelper.h"
#include <Box2D\Box2D.h>

class CDrawManager;
class CInputManager;
class CEntityManager;
class CBox2DManager;
class CStateManager;
class CCamera;

class CEngine
{
public:
	CEngine();
	CDrawManager* drawManager;
	CInputManager* inputManager;
	CEntityManager* entityManager;
	CBox2DManager* box2DManager;
	CStateManager* stateManager;
	CCamera* camera;
	SDL_Window* window;
	SDL_Renderer* renderer;
	b2World* world;
	MusicHelper* musicHelper;
	bool running;
	bool showFPSCounter;
	int fpsCounter;
	int windowHeight, windowWidth;
private:
	void Tick();
	
};

#endif
