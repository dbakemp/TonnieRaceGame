#ifndef CENTITY_H
#define CENTITY_H

#include "IEntityListener.h"

class CEngine;

class CEntity: public IEntityListener {
public:
	CEntity(CEngine *engine);
	void Update();

	int xVel;
	int yVel;
private:

};

#endif CENTITY_H