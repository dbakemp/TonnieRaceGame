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
	Credits,
	Loading,
	Help,
	Scores,
	EnterName,
	GA,
	LevelSelector, 
	ProfileCreation
};

class CStateManager
{
public:
	CStateManager(CEngine* engine);
	~CStateManager();
	void changeState(EGameState state, CEngine* engine);
	void pushState(CGameState* state);
	void popState();

	CGameState* getCurrentState();
private:
	vector<CGameState*> states;
	CEngine* engine;
};

#endif
