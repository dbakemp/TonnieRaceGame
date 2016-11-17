#ifndef CPLAYSTATE_H
#define CPLAYSTATE_H

#include <vector>
#include "SDL.h"
#include "CGameState.h"
#include "CCamera.h"

class CPlayState : public CGameState
{
public:
	void init();
	void init(CEngine* engine);
	void clean();

	void pause();
	void resume();

	void handleEvents(CEngine* engine);
	void update(CEngine* engine);
	void draw(CEngine* engine);

	CPlayState(CEngine* engine);
	~CPlayState();

private:
	CCamera* camera;
};
#endif
