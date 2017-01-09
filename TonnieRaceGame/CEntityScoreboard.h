#ifndef CENTITYSCOREBOARD_H
#define CENTITYSCOREBOARD_H

#include "IDrawListener.h"
#include "ILapCountable.h"
#include "CEntity.h"
#include "CEngine.h"
#include "CUIImage.h"
#include "IInputListener.h"
#include "SDL_ttf.h"
#include "CCamera.h"
#include "CEntityCar.h"

class CEntityScoreboard : public CEntity, public IInputListener
{
public:
	CEntityScoreboard(CEngine* engine);
	~CEntityScoreboard();
	void Update();
	void Input(SDL_Event* event) override;
	void SetCamera(CCamera* camera);
	void SetCar(CEntityCar* car);
	void UpdateContainers();
private:
	std::vector<CEntityCar*> cars;
	CEngine* engine;
	CUIImage* image;
	CCamera* camera;
};

#endif
