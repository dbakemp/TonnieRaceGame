#ifndef CHELPSTATE_H 
#define CHELPSTATE_H

#include <vector>
#include "SDL.h"
#include "CGameState.h"

class CHelpState : public CGameState
{
public:
	void init();
	void init(CEngine* engine);
	void clean();

	void pause();
	void resume();

	void handleEvents(CEngine* engine);
	void update(CEngine* engine);
	void draw(CEngine* engine);
	void input(CEngine* engine, SDL_Event* event);

	CHelpState(CEngine* engine);

private:
};
#endif
