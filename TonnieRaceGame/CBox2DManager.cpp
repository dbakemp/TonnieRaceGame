#include "SDL.h"
#include "CBox2DManager.h"
#include "IBox2DListener.h"
#include <algorithm>

CBox2DManager::CBox2DManager(CEngine* engine)
{
}

void CBox2DManager::AddListener(IBox2DListener* box2DListener)
{
	listeners.push_back(box2DListener);
}

void CBox2DManager::RemoveListener(IBox2DListener* box2DListener)
{
	listeners.erase(std::remove(listeners.begin(), listeners.end(), box2DListener), listeners.end());
}

void CBox2DManager::Tick(b2World* world)
{
	for (IBox2DListener* listener : listeners)
	{
		listener->Create(world);
	}
}

void CBox2DManager::Clear()
{
	listeners.clear();
}

CBox2DManager::~CBox2DManager()
{
}
