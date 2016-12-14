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
#include "IUIEntity.h"
#include <functional>

class CUIImage : public CEntity, public IDrawListener, public IInputListener, public IUIEntity
{
public:
	CUIImage(CEngine* engine);
	CUIImage(CEngine* engine, std::string texture);
	virtual ~CUIImage();

	void Draw(SDL_Renderer* renderer);
	void Update();
	void Input(SDL_Event* event);

	void SetPosition(int x, int y);
	void SetHorizontalAlignment(EUIALignmentHorizontal alignment);
	void SetVerticalAlignment(EUIALignmentVertical alignment);
	void SetHorizontalStretch(EUIStretchHorizontal stretch);
	void SetVerticalStretch(EUIStretchVertical stretch);
	void SetContainer(int x, int y, int w, int h);
	void SetTag(std::string tag);
	void SetClickCallback(std::function<void(IUIEntity*)> callback);
	void SetClickHoldCallback(std::function<void(IUIEntity*)> callback);
	std::string GetTag();
private:
	CEngine* engine;
	SDL_Rect container;
	EUIALignmentHorizontal horizontalAlignment;
	EUIALignmentVertical verticalAlignment;
	EUIStretchHorizontal horizontalStretch;
	EUIStretchVertical verticalStretch;
	std::function<void(IUIEntity*)> clickCallback;
	std::function<void(IUIEntity*)> clickCallHoldback;

	bool mouseDown;

	void PreRender();
};

#endif