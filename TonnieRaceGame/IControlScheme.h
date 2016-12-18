#ifndef ICONTROLSCHEME_H
#define ICONTROLSCHEME_H
#include "IBox2DListener.h"
#include "CEntityTire.h"

class CEntityCar;

class IControlScheme
{
public:
	virtual void Input(SDL_Event* event) = 0;
	virtual void Update() = 0;
	virtual void SetCar(CEntityCar* car) = 0;
	virtual void SetTire(CEntityTire* tire) = 0;
	virtual IControlScheme* GetNewTireScheme() = 0;
	virtual void UpdateFriction() = 0;
	virtual void UpdateDrive() = 0;
	virtual void UpdateTurn() = 0;
	virtual void FinishCallback() = 0;
	CEntityCar* car;
	CEntityTire* tire;
private:
};

#endif
