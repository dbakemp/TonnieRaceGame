#include "CInputManager.h"
#include "IInputListener.h"

void CInputManager::AddListener(IInputListener *inputListener)
{
	listeners.push_back(inputListener);
}

void CInputManager::RemoveListener(IInputListener *inputListener)
{
}

void CInputManager::Tick()
{
	for (IInputListener *listener : listeners) {
		listener->Input();
	}
}
