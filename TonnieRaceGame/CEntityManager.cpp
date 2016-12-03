#include "IEntityListener.h"
#include "CEntityManager.h"

void CEntityManager::AddListener(IEntityListener* entityListener)
{
	listeners.push_back(entityListener);
}

void CEntityManager::RemoveListener(IEntityListener* entityListener)
{
}

void CEntityManager::Tick()
{
	for (IEntityListener* listener : listeners)
	{
		listener->Update();
	}
}

void CEntityManager::Clear()
{
	for (IEntityListener* listener : listeners)
	{
		delete listener;
	}
	listeners.clear();
}
