#ifndef CENTERNAMESTATE_H
#define CENTERNAMESTATE_H

#include <vector>
#include "SDL.h"
#include "AdHelper.h"
#include "CUIButton.h"
#include "CUIImage.h"
#include "CGameState.h"

class CEnterNameState : public CGameState
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
	void OnButtonClick(CUIButton* button);

	CEnterNameState(CEngine* engine);
	~CEnterNameState();
private:
	CEngine* engine;
	std::string P1Name;
	std::string P2Name;
	CUILabel* nameLabel;
};
#endif
