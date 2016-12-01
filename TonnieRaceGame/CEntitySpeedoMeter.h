#ifndef CENTITYSPEEDOMETER_H
#define CENTITYSPEEDOMETER_H

#include "IDrawListener.h"
#include "CCamera.h"
#include "CEntity.h"
#include "CEngine.h"
#include "IBox2DListener.h"
#include "SDL_ttf.h"

class CEntitySpeedoMeter : public CEntity, public IDrawListener
{
public:
	CEntitySpeedoMeter(CEngine* engine, TTF_Font* font);
	~CEntitySpeedoMeter();
	void Update();
	void Draw(SDL_Renderer* renderer);
	void SetChild(IBox2DListener* child);
	IBox2DListener* GetChild();

private:
	IBox2DListener* child;
	CEngine* engine;
};

#endif 
