#ifndef CPLAYSTATE_H
#define CPLAYSTATE_H

#include "SDL.h"
#include "CGameState.h"
#include "CCamera.h"

class CPlayState : public CGameState
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
	void checkSeque();
	void OnFinish(IBox2DListener* car);

	bool shouldSeque;
	EGameState stateSeque;

	CPlayState(CEngine* engine);
	~CPlayState();

private:
	CEngine* engine;
};
#endif
