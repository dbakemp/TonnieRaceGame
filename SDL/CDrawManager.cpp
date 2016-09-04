#include "SDL.h"
#include "CDrawManager.h"
#include "IDrawListener.h"

void CDrawManager::AddListener(IDrawListener *drawListener)
{
	listeners.push_back(drawListener);
}

void CDrawManager::RemoveListener(IDrawListener *drawListener)
{
}

void CDrawManager::Tick(SDL_Renderer *renderer)
{
	for (IDrawListener *listener : listeners) {
		listener->Draw(renderer);
	}
}
