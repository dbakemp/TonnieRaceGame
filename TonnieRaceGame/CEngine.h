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
class CFontManager;
class CDeltaHelper;
class CCollisionHelper;
class CSpriteSheetManager;
class CCamera;
class CAdManager;
class CTextureManager;
class CMap;

class CEngine
{
public:
	CEngine();
	~CEngine();
	AdHelper* adHelper;
	CDrawManager* drawManager;
	CInputManager* inputManager;
	CEntityManager* entityManager;
	CBox2DManager* box2DManager;
	CStateManager* stateManager;
	CDeltaHelper* deltaHelper;
	CAdManager* adManager;
	CMap* currentMap;
	CFontManager* fontManager;
	CCamera* camera;
	SDL_Window* window;
	SDL_Renderer* renderer;
	b2World* world;
	MusicHelper* musicHelper;
	CCollisionHelper* collisionHelper;
	CSpriteSheetManager* spriteSheetManager;
	CTextureManager* textureManager;
	bool running;
	bool showFPSCounter;
	bool gameControllerConnected;
	int fpsCounter;
	std::string level;
	int windowHeight, windowWidth;
private:
	void Tick();
	void ResizeWindow(int width, int height);
};

#endif
