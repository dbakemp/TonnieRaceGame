#ifndef CSCORESSTATE_H
#define CSCORESSTATE_H

#include "SDL.h"
#include "CGameState.h"
#include "CUIImage.h"
#include "CUIButton.h"

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
	void checkSeque();

	bool shouldSeque;
	EGameState stateSeque;

	CScoresState(CEngine* engine);
	~CScoresState();

private:
	void OnButtonClick(CUIButton* button);
	CEngine* engine;
	CUIImage* background;
};
#endif
