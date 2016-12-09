#ifndef CUILABEL_H
#define CUILABEL_H

#include "IDrawListener.h"
#include "IBox2DListener.h"
#include "IInputListener.h"
#include "CEntity.h"
#include "SDL_ttf.h"
#include "CEngine.h"
#include "EUIAlignment.h"

class CUILabel : public CEntity, public IDrawListener, public IInputListener
{
public:
	CUILabel(CEngine* engine);
	CUILabel(CEngine* engine, std::string font, std::string text);

	void Draw(SDL_Renderer* renderer);
	void Update();
	void Input(SDL_Event* event);

	void SetPosition(int x, int y);
	void SetText(std::string text);
	void SetFont(std::string font);
	void SetHorizontalAlignment(EUIALignmentHorizontal alignment);
	void SetVerticalAlignment(EUIALignmentVertical alignment);
	void SetContainer(int x, int y, int w, int h);
	void SetFontSize(int fontSize);
	void SetVisibility(bool visible);

	void ToggleVisibility();

	std::string GetText();
	bool GetVisibility();
private:
	CEngine* engine;
	SDL_Rect container;
	EUIALignmentHorizontal horizontalAlignment;
	EUIALignmentVertical verticalAlignment;
	int fontSize;
	std::string fontName;
	void PreRender();
};

#endif