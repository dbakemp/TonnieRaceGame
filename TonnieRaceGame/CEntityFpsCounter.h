#ifndef CENTITYFPSCOUNTER_H
#define CENTITYFPSCOUNTER_H

#include "IDrawListener.h"
#include "IInputListener.h"
#include "CEntity.h"
#include "CEngine.h"
#include "SDL_ttf.h"

class CEntityFpsCounter : public CEntity, public IDrawListener, public IInputListener
{
public:
	CEntityFpsCounter(CEngine* engine, TTF_Font* font);
	~CEntityFpsCounter();
	void Update();
	void Draw(SDL_Renderer* renderer);
	void Input(SDL_Event* event);
private:
	CEngine* engine;
	double measurement;
};

#endif
