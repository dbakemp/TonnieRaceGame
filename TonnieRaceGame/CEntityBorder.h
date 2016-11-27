#ifndef CENTITYBORDER_H
#define CENTITYBORDER_H

#include "IDrawListener.h"
#include "IBox2DListener.h"
#include "IInputListener.h"
#include "CEntity.h"
#include "CEngine.h"
#include <json\json.h>
#include <vector>
#include <Box2D\Box2D.h>
#include <poly2tri.h>

class CEntityBorder : public CEntity, public IDrawListener, public IBox2DListener, public IInputListener
{
public:
	CEntityBorder(CEngine* engine, p2t::Triangle* triangle);
	void Draw(SDL_Renderer* renderer);
	void Update();
	void Create(b2World* world);
	void Input(SDL_Event* event);
private:
	CEngine* engine;
};

#endif
