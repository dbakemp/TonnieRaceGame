#ifndef CUICONTAINER_H
#define CUICONTAINER_H

#include "IDrawListener.h"
#include "IBox2DListener.h"
#include "IInputListener.h"
#include "CEntity.h"
#include "CUILabel.h"
#include "SDL_ttf.h"
#include "CEngine.h"
#include "IUIEntity.h"
#include <functional>

class CUIContainer : public CEntity, public IDrawListener, public IInputListener, public IUIEntity
{
public:
	CUIContainer(CEngine* engine);
	~CUIContainer();

	void Draw(SDL_Renderer* renderer);
	void Update();
	void Input(SDL_Event* event);

	void SetPosition(int x, int y);
	void SetHorizontalAlignment(EUIALignmentHorizontal alignment);
	void SetVerticalAlignment(EUIALignmentVertical alignment);
	void SetContainer(int x, int y, int w, int h);
	void SetWidth(int width);
	void SetHeight(int height);
	void AddUIElement(IUIEntity* element);
private:
	CEngine* engine;
	SDL_Rect container;
	EUIALignmentHorizontal horizontalAlignment;
	EUIALignmentVertical verticalAlignment;

	SDL_Rect dstrect;
	SDL_Rect srcrect;
	std::vector<IUIEntity*> uiElements;
	
	void PreRender();
};

#endif