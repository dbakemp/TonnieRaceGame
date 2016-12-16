#ifndef CENTITYMANAGER_H
#define CENTITYMANAGER_H

#include <vector>

class IEntityListener;

class CEntityManager
{
public:
	std::vector<IEntityListener*> listeners;

	void AddListener(IEntityListener* entityListener);
	void RemoveListener(IEntityListener* entityListener);
	void Tick();
	void Clear();
	~CEntityManager();
};


#endif
