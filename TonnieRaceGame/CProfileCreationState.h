#ifndef CPROFILECREATIONSTATE_H
#define CPROFILECREATIONSTATE_H

#include "SDL.h"
#include "CGameState.h"
#include "CUIImage.h"
#include "CUIButton.h"

class CProfileCreationState : public CGameState {
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

	std::string currentName;
	char *composition;
	Sint32 cursor;
	Sint32 selection_len;

	CProfileCreationState(CEngine* engine);
	~CProfileCreationState();
private:
	
	void OnButtonClick(CUIButton* button);
	CEngine* engine;
	CUIImage* background;
	CUILabel* profileName;
};

#endif // !CPROFILECREATIONSTATE_H

