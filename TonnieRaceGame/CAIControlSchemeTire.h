#ifndef CAICONTROLSCHEMETIRE_H
#define CAICONTROLSCHEMETIRE_H

#include "IBox2DListener.h"
#include "IControlScheme.h"

class CAIControlSchemeTire : public IControlScheme
{
public:
	explicit CAIControlSchemeTire(CEngine* engine);
	void Input(SDL_Event* event) override;
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
