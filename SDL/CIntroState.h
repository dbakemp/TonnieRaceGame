#ifndef CINTROSTATE_H
#define CINTROSTATE_H

#include <vector>
#include "SDL.h"
#include "CGameState.h"

class CIntroState: public CGameState
{
public:
	void init();
	void clean();

	void pause();
	void resume();

	void handleEvents(CEngine* engine);
	void update(CEngine* engine);
	void draw(CEngine* engine);

private:

};
#endif
