#ifndef CENTITYCAR_H
#define CENTITYCAR_H

#include "IDrawListener.h"
#include "IInputListener.h"
#include "IBox2DListener.h"
#include "CEntity.h"
#include "CEngine.h"
#include "CEntityTire.h"
#include <vector>
#include <Box2D\Box2D.h>

class CEntityCar : public CEntity, public IDrawListener, public IInputListener, public IBox2DListener {
public:
	CEntityCar(CEngine *engine);
	void Draw(SDL_Renderer *renderer);
	void Input(SDL_Event *event);
	void Update();
	void Create(b2World* world);
	b2RevoluteJoint *flJoint, *frJoint;
	std::vector<CEntityTire*> tires;
private:
	CEngine *engine;
};

#endif