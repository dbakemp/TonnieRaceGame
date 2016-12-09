#ifndef CUIIMAGE_H
#define CUIIMAGE_H

#include "IDrawListener.h"
#include "IBox2DListener.h"
#include "IInputListener.h"
#include "CEntity.h"
#include "CUILabel.h"
#include "SDL_ttf.h"
#include "CEngine.h"
#include "EUIStretch.h"
#include <functional>

class CUIImage : public CEntity, public IDrawListener, public IInputListener
{
public:
	CUIImage(CEngine* engine);
	CUIImage(CEngine* engine, std::string texture);

	void Draw(SDL_Renderer* renderer);
	void Update();
	void Input(SDL_Event* event);

	void SetPosition(int x, int y);
	void SetHorizontalAlignment(EUIALignmentHorizontal alignment);
	void SetVerticalAlignment(EUIALignmentVertical alignment);
	void SetHorizontalStretch(EUIStretchHorizontal stretch);
	void SetVerticalStretch(EUIStretchVertical stretch);
private:
	CEngine* engine;
	SDL_Rect container;
	EUIALignmentHorizontal horizontalAlignment;
	EUIALignmentVertical verticalAlignment;
	EUIStretchHorizontal horizontalStretch;
	EUIStretchVertical verticalStretch;

	void PreRender();
};

#endif