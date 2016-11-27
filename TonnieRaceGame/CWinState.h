#ifndef CWINSTATE_H 
#define CWINSTATE_H

#include <vector>
#include "SDL.h"
#include "CGameState.h"

#include "SDL_ttf.h"

class CWinState : public CGameState
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

	CWinState(CEngine* engine);


private:
	TTF_Font* font;
};
#endif
