#ifndef CENTITYCIRCLE_H
#define CENTITYCIRCLE_H

#include "IDrawListener.h"

class CEntityCircle : public IDrawListener {
public:
	CEntityCircle(CEngine *engine);
	void Draw(SDL_Renderer *renderer);
};

#endif
