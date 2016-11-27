#ifndef IDRAWLISTENER_H 
#define IDRAWLISTENER_H

#include "SDL.h"
#include <iostream>
#include "string.h"
#include "SDL_ttf.h"

class CEngine;

class IDrawListener
{
public:
	virtual void Draw(SDL_Renderer* renderer) = 0;
	IDrawListener(CEngine* engine);
	~IDrawListener();
	TTF_Font* font;
	std::string text;
private:
	CEngine* engine;
};


#endif
