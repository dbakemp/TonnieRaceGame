#ifndef CENTITYTIMER_H
#define CENTITYTIMER_H

#include "IDrawListener.h"
#include "CCamera.h"
#include "CEntity.h"
#include "CEngine.h"
#include "CUILabel.h"
#include "CUIContainer.h"
#include "CUIImage.h"
#include "IBox2DListener.h"
#include "SDL_ttf.h"

class CEntityTimer : public CEntity, public IDrawListener, public IInputListener
{
public:
	CEntityTimer(CEngine* engine);
	~CEntityTimer();
	void Update();
	void Draw(SDL_Renderer* renderer);
	void Input(SDL_Event* event) override;
private:
	CEngine* engine;
	CUILabel* label;
};

#endif
