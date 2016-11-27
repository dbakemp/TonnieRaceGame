#include "SDL.h"
#include "CBox2DManager.h"
#include "IBox2DListener.h"

void CBox2DManager::AddListener(IBox2DListener* box2DListener)
{
	listeners.push_back(box2DListener);
}

void CBox2DManager::RemoveListener(IBox2DListener* box2DListener)
{
}

void CBox2DManager::Tick(b2World* world)
{
	for (IBox2DListener* listener : listeners)
	{
		listener->Create(world);
	}
}
