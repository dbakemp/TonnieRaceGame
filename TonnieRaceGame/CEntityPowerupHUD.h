#ifndef CENTITYPOWERUPHUD_H
#define CENTITYPOWERUPHUD_H

#include "IDrawListener.h"
#include "ILapCountable.h"
#include "CEntity.h"
#include "CEngine.h"
#include "CUIImage.h"
#include "IInputListener.h"
#include "SDL_ttf.h"
#include "CCamera.h"
#include "CEntityCar.h"

class CEntityPowerupHUD : public CEntity, public IInputListener
{
public:
	CEntityPowerupHUD(CEngine* engine);
	~CEntityPowerupHUD();
	void Update();
	void Input(SDL_Event* event) override;
	void SetCamera(CCamera* camera);
	void SetCar(CEntityCar* car);
	void UpdateContainers();
private:
	CEntityCar* car;
	CEngine* engine;
	CUIImage* image;
	CCamera* camera;
};

#endif
