#ifndef CPLAYER2CONTROLSCHEMECAR_H
#define CPLAYER2CONTROLSCHEMECAR_H

#include "IBox2DListener.h"
#include "IControlScheme.h"

class CPlayer2ControlSchemeCar : public IControlScheme
{
public:
	void Input(SDL_Event* event) override;
	void Update() override;
	void SetCar(CEntityCar* car) override;
	void SetTire(CEntityTire* tire) override;
	IControlScheme* GetNewTireScheme() override;
private:
};

#endif
