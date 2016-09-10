#ifndef CENTITY_H
#define CENTITY_H

#include "IEntityListener.h"

class CEngine;

class CEntity: public IEntityListener {
public:
	CEntity(CEngine *engine);
	void Update();
	int xPos, yPos;
	int xVel, yVel;
	int height, width;
private:
};

#endif CENTITY_H