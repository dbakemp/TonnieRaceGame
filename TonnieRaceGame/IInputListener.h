#ifndef IINPUTLISTENER_H
#define IINPUTLISTENER_H

#include "SDL.h"

class CEngine;

class IInputListener
{
public:
	virtual void Input(SDL_Event* event) = 0;
	IInputListener(CEngine* engine);
	virtual ~IInputListener();

	int controlState;

	enum InputDirections
	{
		LEFT = 1,
		RIGHT = 2,
		UP = 3,
		DOWN = 4
	};

private:
	CEngine* engine;
};


#endif
