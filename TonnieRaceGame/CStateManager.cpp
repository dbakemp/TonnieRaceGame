#include "SDL.h"
#include "CStateManager.h"
#include "CIntroState.h"
#include "CPlayState.h"
#include "CWinState.h"
#include "CHelpState.h"
#include "CGAState.h"
#include "CScoresState.h"
#include "CCreditsState.h"
#include "CLevelSelectorState.h"

CStateManager::CStateManager(CEngine * engine)
{
	this->engine = engine;
}

CStateManager::~CStateManager()
{
	getCurrentState()->clean(engine);

	for (CGameState* state : states) {
		delete state;
		state = nullptr;
	}
	states.clear();
}

void CStateManager::changeState(EGameState state, CEngine* engine)
{
	if (states.size() > 0) {
		getCurrentState()->clean(engine);
	}

	switch (state)
	{
	case Start: states.push_back(new CIntroState(engine));
		break;
	case Menu: states.push_back(new CIntroState(engine));
		break;
	case Playing: states.push_back(new CPlayState(engine));
		break;
	case Pause: states.push_back(new CIntroState(engine));
		break;
	case Credits: states.push_back(new CCreditsState(engine));
		break;
	case Help: states.push_back(new CHelpState(engine));
		break;
	case Win: states.push_back(new CWinState(engine));
		break;
	case Scores: states.push_back(new CScoresState(engine));
		break;
	case GA: states.push_back(new CGAState(engine));
		break;
	case LevelSelector: states.push_back(new CLevelSelectorState(engine));
		break;
	}
	return;
}

void CStateManager::pushState(CGameState* state)
{
	states.push_back(state);
	return;
}

void CStateManager::popState()
{
	states.pop_back();
	return;
}

CGameState* CStateManager::getCurrentState()
{
	CGameState* currentState = states.back();
	return currentState;
}
