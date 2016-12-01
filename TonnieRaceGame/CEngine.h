#ifndef CENGINE_H
#define CENGINE_H

#include "SDL.h"
#include "MusicHelper.h"
#include <Box2D\Box2D.h>

class AdHelper;
class CDrawManager;
class CInputManager;
class CEntityManager;
class CBox2DManager;
class CStateManager;
class CDeltaHelper;
class CCollisionHelper;
class CCamera;
class CAdManager;
class CMap;

class CEngine
{
public:
	CEngine(); 
	AdHelper* adHelper;
	CDrawManager* drawManager;
	CInputManager* inputManager;
	CEntityManager* entityManager;
	CBox2DManager* box2DManager;
	CStateManager* stateManager;
	CDeltaHelper* deltaHelper;
	CAdManager* adManager;
	CMap* currentMap;
	CCamera* camera;
	SDL_Window* window;
	SDL_Renderer* renderer;
	b2World* world;
	MusicHelper* musicHelper;
	CCollisionHelper* collisionHelper;
	bool running;
	bool showFPSCounter;
	bool gameControllerConnected;
	int fpsCounter;
	int level;
	int windowHeight, windowWidth;
private:
	void Tick();
	void ResizeWindow(int width, int height);
};

#endif
