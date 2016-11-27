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
	IDrawListener(CEngine* engine, int zIndex);
	~IDrawListener();
	void ChangeZIndex(int index);
	TTF_Font* font;
	std::string text;
	bool visible;
	bool debugVisible;
	int zIndex;
private:
	CEngine* engine;
};


#endif
