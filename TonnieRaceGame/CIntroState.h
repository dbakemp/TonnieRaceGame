#ifndef CINTROSTATE_H
#define CINTROSTATE_H

#include <vector>
#include "SDL.h"
#include "CGameState.h"

class CIntroState: public CGameState
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

	

	int selectedItem;
	

	CIntroState(CEngine* engine);

private:
	SDL_Surface* background;
	int lastState;
	void SelectLeft();
	void SelectRight();
	void SelectOption(CEngine* engine);
};
#endif
