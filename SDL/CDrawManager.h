#ifndef CDRAWMANAGER_H
#define CDRAWMANAGER_H
#include "SDL.h"
#include <vector>

class IDrawListener;

class CDrawManager
{
public:
	std::vector<IDrawListener*> listeners;

	void AddListener(IDrawListener* drawListener);
	void RemoveListener(IDrawListener* drawListener);
	void Tick(SDL_Renderer* renderer);
};


#endif 
