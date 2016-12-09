#ifndef CUIBUTTON_H
#define CUIBUTTON_H

#include "IDrawListener.h"
#include "IBox2DListener.h"
#include "IInputListener.h"
#include "CEntity.h"
#include "CUILabel.h"
#include "SDL_ttf.h"
#include "CEngine.h"
#include <functional>

class CUIButton : public CEntity, public IDrawListener, public IInputListener
{
public:
	CUIButton(CEngine* engine);
	CUIButton(CEngine* engine, std::string font, std::string text, std::string texture);

	void Draw(SDL_Renderer* renderer);
	void Update();
	void Input(SDL_Event* event);

	void SetPosition(int x, int y);
	void SetText(std::string text);
	void SetFont(std::string font);
	void SetHorizontalAlignment(EUIALignmentHorizontal alignment);
	void SetVerticalAlignment(EUIALignmentVertical alignment);
	void SetClickCallback(std::function<void(CUIButton*)> callback);
	void SetFontSize(int fontSize);

	std::string GetText();
private:
	CEngine* engine;
	CUILabel* label;
	SDL_Rect container;
	EUIALignmentHorizontal horizontalAlignment;
	EUIALignmentVertical verticalAlignment;
	std::function<void(CUIButton*)> clickCallback;

	void PreRender();
};

#endif