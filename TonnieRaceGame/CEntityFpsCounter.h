#ifndef CENTITYFPSCOUNTER_H
#define CENTITYFPSCOUNTER_H

#include "IDrawListener.h"
#include "IInputListener.h"
#include "CEntity.h"
#include "CEngine.h"
#include "SDL_ttf.h"
#include "CUILabel.h"

class CEntityFpsCounter : public CEntity, public IDrawListener, public IInputListener
{
public:
	CEntityFpsCounter(CEngine* engine);
	~CEntityFpsCounter();
	void Update();
	void Draw(SDL_Renderer* renderer);
	void Input(SDL_Event* event);
private:
	CEngine* engine; 
	int tickindex = 0;
	int ticksum = 0;
	int ticklist[500];
	CUILabel* label;
};

#endif
