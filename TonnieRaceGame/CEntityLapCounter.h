#ifndef CENTITYLAPCOUNTER_H
#define CENTITYLAPCOUNTER_H

#include "IDrawListener.h"
#include "ILapCountable.h"
#include "CEntity.h"
#include "CEngine.h"
#include "CUILabel.h"
#include "SDL_ttf.h"

class CEntityLapCounter : public CEntity {
public:
	CEntityLapCounter(CEngine* engine);
	~CEntityLapCounter();
	void Update();
	void SetLapCountable(ILapCountable* lapCountable);
	ILapCountable* GetLapCountable();
private:
	ILapCountable* lapCountable;
	CEngine* engine;
	CUILabel* label;
};

#endif
