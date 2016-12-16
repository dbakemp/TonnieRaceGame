#ifndef CHELPSTATE_H
#define CHELPSTATE_H

#include "SDL.h"
#include "CGameState.h"
#include "CUIButton.h"

class CHelpState : public CGameState
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

	CHelpState(CEngine* engine);

private:
	void OnButtonClick(CUIButton* button);
	CEngine* engine;
};
#endif
