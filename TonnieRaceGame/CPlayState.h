#ifndef CPLAYSTATE_H
#define CPLAYSTATE_H

#include <vector>
#include "SDL.h"
#include "CGameState.h"
#include "CCamera.h"

class CPlayState : public CGameState
{
public:
	void init();
	void init(CEngine* engine);
	void clean();

	void pause();
	void resume();

	void handleEvents(CEngine* engine);
	void update(CEngine* engine);
	void drawFPSCounter(CEngine* engine);
	void draw(CEngine* engine);

	CPlayState(CEngine* engine);
	~CPlayState();

	//temp
	int texW = 0;
	int texH = 0;
	SDL_Texture* backmapTexture;
private:
	CCamera* camera;
};
#endif
