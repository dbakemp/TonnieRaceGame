#ifndef IBOX2DLISTENER_H 
#define IBOX2DLISTENER_H

#include "SDL.h"
#include <Box2D\Box2D.h>

class CEngine;

class IBox2DListener
{
public:
	virtual void Create(b2World* world) = 0;
	IBox2DListener(CEngine* engine);
	virtual ~IBox2DListener();

	b2BodyDef bodyDef;
	b2Body* body;
	b2PolygonShape polygon;
	b2FixtureDef fixture;
private:
	CEngine* engine;
};


#endif
