#ifndef CENTITYLAPCOUNTER_H
#define CENTITYLAPCOUNTER_H

#include "IDrawListener.h"
#include "ILapCountable.h"
#include "CEntity.h"
#include "CEngine.h"
#include "CUILabel.h"
#include "IInputListener.h"
#include "SDL_ttf.h"
#include "CCamera.h"
#include "CEntityCar.h"

class CEntityLapCounter : public CEntity, public IInputListener
{
public:
	CEntityLapCounter(CEngine* engine);
	~CEntityLapCounter();
	void Update();
	void Input(SDL_Event* event) override;
	void SetLapCountable(ILapCountable* lapCountable);
	ILapCountable* GetLapCountable();
	void SetCamera(CCamera* camera);
	void SetCar(CEntityCar* car);
	void UpdateContainers();
private:
	ILapCountable* lapCountable;
	CEngine* engine;
	CUILabel* label;
	CCamera* camera;
	CEntityCar* car;
};

#endif
