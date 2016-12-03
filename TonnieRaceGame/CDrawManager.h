#ifndef CDRAWMANAGER_H
#define CDRAWMANAGER_H
#include "SDL.h"
#include <vector>

class IDrawListener;

class CDrawManager
{
public:
	std::vector<IDrawListener*> listeners;
	std::vector<IDrawListener*> listenersIndexed[30];

	enum class Layers { Tile = 5, Object = 15, UI = 25};

	void AddListener(IDrawListener* drawListener, int index);
	void RemoveListener(IDrawListener* drawListener);
	void Tick(SDL_Renderer* renderer);
	void ChangeZIndex(IDrawListener* drawListener, int index);
	void Clear();
};


#endif 
