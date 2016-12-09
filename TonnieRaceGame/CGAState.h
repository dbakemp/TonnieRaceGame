#ifndef CGASTATE_H
#define CGASTATE_H

#include <vector>
#include "SDL.h"
#include "CGameState.h"
#include "CCamera.h"

class CGAState : public CGameState
{
public:
	void init(CEngine* engine);
	void clean(CEngine* engine);

	void pause();
	void resume();

	void handleEvents(CEngine* engine);
	void update(CEngine* engine);
	void draw(CEngine* engine);
	void input(CEngine* engine, SDL_Event* event);
	void OnFinish(IBox2DListener* car);

	CGAState(CEngine* engine);
	~CGAState();

	//temp
	int texW = 0;
	int texH = 0;
	int GATicks = 0;
	SDL_Texture* backmapTexture;
private:
	CCamera* camera;
	CEngine* engine;
};
#endif
