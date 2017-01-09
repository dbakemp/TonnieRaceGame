#ifndef CLOADINGSTATE_H
#define CLOADINGSTATE_H

#include "SDL.h"
#include "CGameState.h"
#include "CUIButton.h"

class CLoadingState : public CGameState
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

	CLoadingState(CEngine* engine);

private:
	void OnButtonClick(CUIButton* button);
	CEngine* engine;
};
#endif
