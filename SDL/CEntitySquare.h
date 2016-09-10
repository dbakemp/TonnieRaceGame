#ifndef CENTITYSQUARE_H
#define CENTITYSQUARE_H

#include "IDrawListener.h"
#include "IInputListener.h"
#include "CEntity.h"

class CEntitySquare : public CEntity, public IDrawListener, public IInputListener {
public:
	CEntitySquare(CEngine *engine);
	void Draw(SDL_Renderer *renderer);
	void Input(SDL_Event *event);
	void Update();
	int rCol, gCol, bCol;
	float friction;
private:
	CEngine *engine;
};

#endif
