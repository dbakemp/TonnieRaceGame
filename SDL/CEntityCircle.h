#ifndef CENTITYCIRCLE_H
#define CENTITYCIRCLE_H

#include "IDrawListener.h"
#include "CEntity.h"

class CEntityCircle : public CEntity, public IDrawListener {
public:
	CEntityCircle(CEngine *engine);
	void Draw(SDL_Renderer *renderer);
	void Update();
	int rCol, gCol, bCol;
private:
	CEngine *engine;
};

#endif
