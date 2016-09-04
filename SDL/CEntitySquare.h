#ifndef CENTITYSQUARE_H
#define CENTITYSQUARE_H

#include "IDrawListener.h"
#include "IInputListener.h"

class CEntitySquare : public IDrawListener, public IInputListener {
public:
	CEntitySquare(CEngine *engine);
	void Draw(SDL_Renderer *renderer);
	void Input(SDL_Event *event);
};

#endif
