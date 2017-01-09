#ifndef CENTITYFINISHED_H
#define CENTITYFINISHED_H

#include "IDrawListener.h"
#include "ILapCountable.h"
#include "CEntity.h"
#include "CEngine.h"
#include "CUILabel.h"
#include "IInputListener.h"
#include "SDL_ttf.h"
#include "CCamera.h"
#include "CEntityCar.h"

class CEntityFinished : public CEntity, public IInputListener
{
public:
	CEntityFinished(CEngine* engine);
	~CEntityFinished();
	void Update();
	void Input(SDL_Event* event) override;
	void SetCamera(CCamera* camera);
	void SetCar(CEntityCar* car);
	void UpdateContainers();
private:
	CEntityCar* car;
	CEngine* engine;
	CUILabel* label;
	CCamera* camera;
};

#endif
