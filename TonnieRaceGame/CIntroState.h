#ifndef CINTROSTATE_H
#define CINTROSTATE_H

#include <vector>
#include "SDL.h"
#include "AdHelper.h"
#include "CUIButton.h"
#include "CGameState.h"

class CIntroState: public CGameState
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
	
	bool shouldSeque;
	EGameState stateSeque;

	CIntroState(CEngine* engine);
private:
	void OnButtonClick(CUIButton* button);
	CEngine* engine;
};
#endif
