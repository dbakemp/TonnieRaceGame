#include "SDL.h"
#include "CDrawManager.h"
#include "IDrawListener.h"
#include <algorithm>

void CDrawManager::AddListener(IDrawListener* drawListener, int index)
{
	listeners.push_back(drawListener);
	listenersIndexed[index].push_back(drawListener);
}

void CDrawManager::RemoveListener(IDrawListener* drawListener)
{

}

void CDrawManager::Tick(SDL_Renderer* renderer)
{
	for (std::vector<IDrawListener*> listeners : listenersIndexed)
	{
		for (IDrawListener* listener : listeners)
		{
			listener->Draw(renderer);
		}
	}
}

void CDrawManager::ChangeZIndex(IDrawListener* drawListener, int index)
{
	listenersIndexed[drawListener->zIndex].erase(std::remove(listenersIndexed[drawListener->zIndex].begin(), listenersIndexed[drawListener->zIndex].end(), drawListener), listenersIndexed[drawListener->zIndex].end());
	listenersIndexed[index].push_back(drawListener);
}
