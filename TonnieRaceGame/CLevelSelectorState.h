#ifndef CLEVELSELECTORSTATE_H
#define CLEVELSELECTORSTATE_H

#include <vector>
#include "SDL.h"
#include "AdHelper.h"
#include "CUIButton.h"
#include "CGameState.h"
#include "CUIButton.h"
#include "CGameState.h"
#include "CUIHorizontalScrollView.h"
#include "CStateManager.h"
#include <json\json.h>

class CLevelSelectorState : public CGameState
{
public:
	CLevelSelectorState(CEngine* engine);
	~CLevelSelectorState();

	void init(CEngine* engine);
	void clean(CEngine* engine);
	
	void addLevel(std::string image, std::string map);

	void SelectLevel(IUIEntity* entity);

	void pause();
	void resume();

	void handleEvents(CEngine* engine);
	void update(CEngine* engine);
	void draw(CEngine* engine);
	void input(CEngine* engine, SDL_Event* event);
	void checkSeque();

	void ScrollLeft();
	void ScrollRight();

	bool shouldSeque;
	EGameState stateSeque;

private:
	void OnButtonClick(CUIButton* button);
	CEngine* engine;
	CUIHorizontalScrollView* scrollView;
};
#endif
