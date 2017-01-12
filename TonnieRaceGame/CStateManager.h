#ifndef CSTATEMANAGER_H
#define CSTATEMANAGER_H

#include <vector>
#include "CGameState.h"

using namespace std;

enum EGameState
{
	Start,
	Menu,
	Playing,
	Pause,
	Resumed,
	Credits,
	Loading,
	Help,
	Scores,
	EnterName,
	GA,
	LevelSelector, 
	ProfileCreation
};

#include "CPlayState.h"

class CStateManager
{
public:
	CStateManager(CEngine* engine);
	~CStateManager();
	void changeState(EGameState state, CEngine* engine, bool clean = true);
	void pushState(CGameState* state);
	void popState();
	void changeStateToPause(CEngine* engine, CPlayState* playState);
	CGameState* getCurrentState();
	CPlayState* playState;
private:
	vector<CGameState*> states;
	CEngine* engine;
};

#endif
