#ifndef CENTITY_H
#define CENTITY_H

#include "IEntityListener.h"

class CEngine;


class CEntity: public IEntityListener
{
public:

	CEntity(CEngine* engine);
	~CEntity();
	void Update();
	virtual void CollisionBegin(CEntity* collider);
	virtual void CollisionEnd(CEntity* collider);
	enum class Type { CAR, CHECKPOINT, WAYPOINT, POWERUP };
	void SetType(Type type);
	Type GetType();
	float xPos, yPos;
	float xVel, yVel;
	float xAcc, yAcc;
	int height, width;
private:
	Type type;
};

#endif CENTITY_H
