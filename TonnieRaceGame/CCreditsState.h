#ifndef CCREDITSSTATE_H
#define CCREDITSSTATE_H

#include <vector>
#include "SDL.h"
#include "CGameState.h"

class CCreditsState : public CGameState
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

	CCreditsState(CEngine* engine);

private:
};
#endif
