#include "IEntityListener.h"
#include "CEntityManager.h"
#include <algorithm>

void CEntityManager::AddListener(IEntityListener* entityListener)
{
	listeners.push_back(entityListener);
}

void CEntityManager::RemoveListener(IEntityListener* entityListener)
{
	listeners.erase(std::remove(listeners.begin(), listeners.end(), entityListener), listeners.end());
}

void CEntityManager::Tick()
{
	int count = listeners.size();
	for (int i = count - 1; i >= 0; i--) {
		listeners[i]->Update();
		if (listeners[i]->shouldDelete) {
			delete listeners[i];
		}
	}
}

void CEntityManager::Clear()
{
	int count = listeners.size();
	for (int i = count-1; i >= 0; i--) {
		delete listeners[i];
	}
	listeners.clear();
}
