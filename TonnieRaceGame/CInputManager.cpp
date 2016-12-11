#include "SDL.h"
#include "CInputManager.h"
#include "IInputListener.h"
#include <algorithm>

void CInputManager::AddListener(IInputListener* inputListener)
{
	listeners.push_back(inputListener);
}

void CInputManager::RemoveListener(IInputListener* inputListener)
{
	listeners.erase(std::remove(listeners.begin(), listeners.end(), inputListener), listeners.end());
}

void CInputManager::Tick(SDL_Event* event)
{
	for (IInputListener* listener : listeners)
	{
		listener->Input(event);
	}
}

void CInputManager::Clear()
{
	listeners.clear();
}
