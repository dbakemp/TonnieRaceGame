#ifndef CUIHORIZONTALSCROLLVIEW_H
#define CUIHORIZONTALSCROLLVIEW_H

#include "IDrawListener.h"
#include "IBox2DListener.h"
#include "IInputListener.h"
#include "CEntity.h"
#include "CUILabel.h"
#include "CUIContainer.h"
#include "CEngine.h"
#include "IUIEntity.h"

class CUIHorizontalScrollView : public CEntity, public IDrawListener, public IInputListener, public IUIEntity
{
public:
	CUIHorizontalScrollView(CEngine* engine);
	virtual ~CUIHorizontalScrollView();

	void Draw(SDL_Renderer* renderer);
	void Update();
	void Input(SDL_Event* event);

	void SetPosition(int x, int y);
	void SetHorizontalAlignment(EUIALignmentHorizontal alignment);
	void SetVerticalAlignment(EUIALignmentVertical alignment);
	void SetContainer(int x, int y, int w, int h);
	void SetWidth(int width);
	void SetHeight(int height);
	void Scroll(int scroll);
	SDL_Rect GetRectangle();
	void SetTag(std::string tag);
	std::string GetTag();

	void ScrollToNext();
	void ScrollToPrevious();

	void AddUIElement(IUIEntity* element);
private:
	CEngine* engine;
	SDL_Rect container;
	IUIEntity* currentSelectedEntity;
	int currentSelectedEntityIndex;
	EUIALignmentHorizontal horizontalAlignment;
	EUIALignmentVertical verticalAlignment;
	CUIContainer* elementContainer;
	std::vector<IUIEntity*> containerElements;
	int scrollAmount;
	int toScrollAmount;

	void PreRender();
};

#endif
