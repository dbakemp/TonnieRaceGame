#ifndef CSCORESSTATE_H
#define CSCORESSTATE_H

#include <vector>
#include "SDL.h"
#include "CGameState.h"

class CScoresState : public CGameState
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

	CScoresState(CEngine* engine);

private:
};
#endif
