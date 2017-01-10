#ifndef CENTITYSPEEDOMETER_H
#define CENTITYSPEEDOMETER_H

#include "IDrawListener.h"
#include "CCamera.h"
#include "CEntity.h"
#include "CEngine.h"
#include "CUILabel.h"
#include "CUIContainer.h"
#include "CUIImage.h"
#include "IBox2DListener.h"
#include "SDL_ttf.h"
#include "CEntityCar.h"

class CEntitySpeedoMeter : public CEntity, public IDrawListener, public IInputListener
{
public:
	CEntitySpeedoMeter(CEngine* engine);
	~CEntitySpeedoMeter();
	void Update();
	void Draw(SDL_Renderer* renderer);
	void Input(SDL_Event* event) override;
	void SetChild(IBox2DListener* child);
	IBox2DListener* GetChild();
	void SetCamera(CCamera* camera);
	void UpdateContainers();
	void SetCar(CEntityCar* car);

private:
	IBox2DListener* child;
	SDL_Surface* meter;
	SDL_Texture* meter_texture;
	SDL_Surface* meterback;
	SDL_Texture* meterback_texture;
	CEngine* engine;
	int angle;
	SDL_Point point;
	CUILabel* speedLabel;
	CUIContainer* labelContainer;
	CUIImage* speedometer;
	int tickindex = 0;
	float32 ticksum = 0;
	float32 ticklist[200];
	CCamera* camera;
	CEntityCar* car;
};

#endif
