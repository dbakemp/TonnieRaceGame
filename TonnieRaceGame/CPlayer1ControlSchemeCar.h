#ifndef CPLAYER1CONTROLSCHEMECAR_H
#define CPLAYER1CONTROLSCHEMECAR_H

#include "IBox2DListener.h"
#include "IControlScheme.h"

class CPlayer1ControlSchemeCar : public IControlScheme
{
public:
	explicit CPlayer1ControlSchemeCar(CEngine* engine);
	void Input(SDL_Event* event) override;
	//void TeleportCar();
	void Update() override; 
	void SetCar(CEntityCar* car) override;
	void SetTire(CEntityTire* tire) override;
	void UpdateFriction() override;
	void UpdateDrive() override;
	void UpdateTurn() override;
	void FinishCallback() override;
	IControlScheme* GetNewTireScheme() override;
private:
	CEngine* engine;
};

#endif
