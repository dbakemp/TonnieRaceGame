#ifndef CENTITY_H
#define CENTITY_H

#include "IEntityListener.h"

class CEngine;

class CEntity: public IEntityListener {
public:
	CEntity(CEngine *engine);
	void Update();
	float xPos, yPos;
	float xVel, yVel;
	float xAcc, yAcc;
	int height, width;
private:
};

#endif CENTITY_H