#ifndef CENTITYSQUARE_H
#define CENTITYSQUARE_H

#include "IDrawListener.h"
#include "IInputListener.h"
#include "IBox2DListener.h"
#include "CEntity.h"
#include <Box2D\Box2D.h>

class CEntitySquare : public CEntity, public IDrawListener, public IInputListener, public IBox2DListener {
public:
	CEntitySquare(CEngine *engine);
	void Draw(SDL_Renderer *renderer);
	void Input(SDL_Event *event);
	void Update();
	void Create(b2World* world);
	int rCol, gCol, bCol;
	float friction;
private:
	CEngine *engine;
};

#endif
