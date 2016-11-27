#ifndef CENTITYMANAGER_H
#define CENTITYMANAGER_H
#include "SDL.h"
#include <vector>

class IEntityListener;

class CEntityManager
{
public:
	std::vector<IEntityListener*> listeners;

	void AddListener(IEntityListener* entityListener);
	void RemoveListener(IEntityListener* entityListener);
	void Tick();
};


#endif
