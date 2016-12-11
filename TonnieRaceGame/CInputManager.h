#ifndef CDINPUTMANAGER_H
#define CDINPUTMANAGER_H
#include "SDL.h"
#include <vector>

class IInputListener;

class CInputManager
{
public:
	std::vector<IInputListener*> listeners;

	void AddListener(IInputListener* inputListener);
	void RemoveListener(IInputListener* inputListener);
	void Tick(SDL_Event* event);
	void Clear();

	~CInputManager();
};


#endif
