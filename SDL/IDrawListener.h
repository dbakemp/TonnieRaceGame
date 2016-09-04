#ifndef IDRAWLISTENER_H 
#define IDRAWLISTENER_H

#include "SDL.h"

class CEngine;

class IDrawListener {
public:
	virtual void Draw(SDL_Renderer *renderer) = 0;
	IDrawListener(CEngine *engine);
	~IDrawListener();

	int xPos;
	int yPos;
private:
	CEngine *engine;
};


#endif
