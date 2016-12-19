#ifndef CENTITYPOSITIONCOUNTER_H
#define CENTITYPOSITIONCOUNTER_H

#include "IDrawListener.h"
#include "ILapCountable.h"
#include "CEntity.h"
#include "CEngine.h"
#include "CUILabel.h"
#include "IInputListener.h"
#include "CCamera.h"
#include "CEntityCar.h"
#include "CEntityCar.h"

class CEntityPositionCounter : public CEntity, public IInputListener
{
public:
	CEntityPositionCounter(CEngine* engine);
	~CEntityPositionCounter();
	void Update();
	void Input(SDL_Event* event) override;
	void SetCar(CEntityCar* car);
	void SetCamera(CCamera* camera);
	void UpdateContainers();
private:
	CEntityCar* car;
	CEngine* engine;
	CUILabel* label;
	CCamera* camera;
};

#endif
