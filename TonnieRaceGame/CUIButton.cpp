#include "CUIButton.h"
#include "CDrawManager.h"
#include "EUIAlignment.h"
#include "SDL_image.h"
#include "CTextureManager.h"

CUIButton::CUIButton(CEngine * engine) : CEntity(engine), IInputListener(engine), IDrawListener(engine,  (int)CDrawManager::Layers::UI)
{
	this->engine = engine;
	this->container = { 0, 0, 0, 0 };
}

CUIButton::CUIButton(CEngine * engine, std::string font, std::string text, std::string texture) : CEntity(engine), IInputListener(engine), IDrawListener(engine, (int)CDrawManager::Layers::UI)
{
	this->engine = engine;

	this->texture = engine->textureManager->GetTexture(texture);

	this->container = { 0, 0, 0, 0 };

	label = new CUILabel(engine);
	label->SetFont(font);
	label->SetText(text);
	label->SetHorizontalAlignment(EUIALignmentHorizontal::CENTER);
	label->SetVerticalAlignment(EUIALignmentVertical::CENTER);
	label->ChangeZIndex(zIndex + 1);
	label->SetPosition(0, -2);
}

void CUIButton::Draw(SDL_Renderer * renderer)
{
	SDL_RenderCopy(engine->renderer, texture, NULL, &dstrect);
}

void CUIButton::Update()
{
}

void CUIButton::Input(SDL_Event* event)
{
	if (event->type == SDL_MOUSEBUTTONDOWN) {
		if ((event->motion.x > dstrect.x && event->motion.x < dstrect.x + dstrect.w) && (event->motion.y > dstrect.y && event->motion.y < dstrect.y + dstrect.h)) {
			clickCallback(this);
		}
	}
	else if (event->type == SDL_WINDOWEVENT) {
		switch (event->window.event) {
			case SDL_WINDOWEVENT_RESIZED:
				PreRender();
				break;
		}
	}
}

void CUIButton::SetPosition(int x, int y)
{
	this->xPos = x;
	this->yPos = y;
	PreRender();
}

void CUIButton::SetText(std::string text)
{
	label->SetText(text);
}

void CUIButton::SetFont(std::string font)
{
	label->SetFont(font);
}

void CUIButton::SetHorizontalAlignment(EUIALignmentHorizontal alignment)
{
	horizontalAlignment = alignment;
	PreRender();
}

void CUIButton::SetVerticalAlignment(EUIALignmentVertical alignment)
{
	verticalAlignment = alignment;
	PreRender();
}

void CUIButton::PreRender()
{
	SDL_QueryTexture(texture, NULL, NULL, &srcrect.w, &srcrect.h);

	int x = 0;
	int y = 0;

	int wOffset = engine->windowWidth;
	int hOffset = engine->windowHeight;
	int xOffset = 0;
	int yOffset = 0;

	if (container.w != 0 || container.h != 0 || container.x != 0 || container.y != 0) {
		wOffset = container.w;
		hOffset = container.h;
		xOffset = container.x;
		yOffset = container.y;
	}

	switch (horizontalAlignment) {
	case EUIALignmentHorizontal::LEFT:
		x = xPos;
		break;
	case EUIALignmentHorizontal::CENTER:
		x = (wOffset / 2) - (srcrect.w / 2) + xOffset + xPos;
		break;
	case EUIALignmentHorizontal::RIGHT:
		x = wOffset - srcrect.w + xPos;
		break;
	}

	switch (verticalAlignment) {
	case EUIALignmentVertical::TOP:
		y = yPos;
		break;
	case EUIALignmentVertical::CENTER:
		y = (hOffset / 2) - (srcrect.h / 2) + yOffset + yPos;
		break;
	case EUIALignmentVertical::BOTTOM:
		y = hOffset - srcrect.h + yPos;
		break;
	}

	dstrect = { x, y, srcrect.w, srcrect.h };

	label->SetContainer(dstrect.x, dstrect.y, dstrect.w, dstrect.h);
}

void CUIButton::SetClickCallback(std::function<void(CUIButton*)> callback)
{
	this->clickCallback = callback;
}

void CUIButton::SetFontSize(int fontSize)
{
	label->SetFontSize(fontSize);
}

std::string CUIButton::GetText()
{
	return label->GetText();
}

