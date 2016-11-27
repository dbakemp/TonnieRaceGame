#ifndef CENTITYCIRCLE_H
#define CENTITYCIRCLE_H

#include "IDrawListener.h"
#include "IBox2DListener.h"
#include "CEntity.h"

class CEntitySmallSquare : public CEntity, public IDrawListener, public IBox2DListener {
public:
	CEntitySmallSquare(CEngine *engine);
	void Draw(SDL_Renderer *renderer);
	void Update();
	void Create(b2World* world);
	int rCol, gCol, bCol;
private:
	CEngine *engine;
};

#endif
