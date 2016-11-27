#ifndef CCOLLISIONHELPER_H
#define CCOLLISIONHELPER_H

#include <Box2D\Box2D.h>
#include <iostream>
#include <string>
#include <vector>


class CCollisionHelper: public b2ContactListener
{
public:
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
private:
};

#endif
