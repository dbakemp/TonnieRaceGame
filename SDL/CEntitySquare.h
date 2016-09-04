#ifndef CENTITYSQUARE_H
#define CENTITYSQUARE_H

#include "IDrawListener.h"

class CEntitySquare : public IDrawListener {
public:
	CEntitySquare(CEngine *engine);
	void Draw(SDL_Renderer *renderer);
};

#endif
