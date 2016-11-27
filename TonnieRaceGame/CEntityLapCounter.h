#ifndef CENTITYLAPCOUNTER_H
#define CENTITYLAPCOUNTER_H

#include "IDrawListener.h"
#include "ILapCountable.h"
#include "CEntity.h"
#include "CEngine.h"
#include "SDL_ttf.h"

class CEntityLapCounter : public CEntity, public IDrawListener
{
public:
	CEntityLapCounter(CEngine* engine, TTF_Font* font);
	~CEntityLapCounter();
	void Update();
	void Draw(SDL_Renderer* renderer);
	void SetLapCountable(ILapCountable* lapCountable);
	ILapCountable* GetLapCountable();
private:
	ILapCountable* lapCountable;
	CEngine* engine;
};

#endif
