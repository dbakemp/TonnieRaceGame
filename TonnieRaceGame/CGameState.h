#ifndef CGAMESTATE_H
#define CGAMESTATE_H

#include <vector>
#include "SDL.h"
#include "CEngine.h"

using namespace std;

class CGameState
{
public:
	virtual void init() = 0;
	virtual void clean() = 0;

	virtual void pause() = 0;
	virtual void resume() = 0;

	virtual void handleEvents(CEngine* engine) = 0;
	virtual void update(CEngine* engine) = 0;
	virtual void draw(CEngine* engine) = 0;
	virtual void input(CEngine* engine, SDL_Event* event) = 0;
private:
};

#endif
