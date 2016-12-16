#include "CUILabel.h"
#include "CDrawManager.h"
#include "CFontManager.h"

CUILabel::CUILabel(CEngine* engine) : CEntity(engine), IInputListener(engine), IDrawListener(engine, (int)CDrawManager::Layers::UI)
{
	this->engine = engine;
	this->xPos = 0;
	this->yPos = 0;
	this->text = "";
	this->font = nullptr;
	this->fontSize = 16;
	this->horizontalAlignment = EUIALignmentHorizontal::LEFT;
	this->verticalAlignment = EUIALignmentVertical::TOP;
	this->container = {0, 0, 0, 0};
	this->visible = true;
}

CUILabel::CUILabel(CEngine* engine, std::string font, std::string text) : CEntity(engine), IInputListener(engine), IDrawListener(engine, (int)CDrawManager::Layers::UI)
{
	this->engine = engine;
	this->xPos = 0;
	this->yPos = 0;
	this->fontSize = 16;
	this->horizontalAlignment = EUIALignmentHorizontal::LEFT;
	this->verticalAlignment = EUIALignmentVertical::TOP;
	this->container = {0, 0, 0, 0};
	this->visible = true;

	SetFont(font);
	SetText(text);
}

CUILabel::~CUILabel()
{
	text.clear();
	engine = nullptr;
}

void CUILabel::Draw(SDL_Renderer* renderer)
{
	if (!visible) { return; }
	SDL_RenderCopy(engine->renderer, texture, NULL, &dstrect);

	if (!debugVisible) { return; }
	SDL_RenderDrawRect(engine->renderer, &dstrect);
}

void CUILabel::Update()
{
}

void CUILabel::Input(SDL_Event* event)
{
	if (event->type == SDL_WINDOWEVENT)
	{
		switch (event->window.event)
		{
		case SDL_WINDOWEVENT_RESIZED:
			PreRender();
			break;
		}
	}
	else if (event->type == SDL_KEYDOWN)
	{
		switch (event->key.keysym.sym)
		{
		case SDLK_f:
			debugVisible = !debugVisible;
			break;
		}
	}
}

void CUILabel::SetPosition(int x, int y)
{
	this->xPos = x;
	this->yPos = y;
	this->UIXPos = this->xPos;
	this->UIYPos = this->yPos;
	PreRender();
}

void CUILabel::SetText(std::string text)
{
	this->text = text;
	PreRender();
}

void CUILabel::SetFont(std::string font)
{
	this->fontName = font;
	this->font = engine->fontManager->GetFont(font, fontSize);
	PreRender();
}

void CUILabel::SetHorizontalAlignment(EUIALignmentHorizontal alignment)
{
	horizontalAlignment = alignment;
	PreRender();
}

void CUILabel::SetVerticalAlignment(EUIALignmentVertical alignment)
{
	verticalAlignment = alignment;
	PreRender();
}

void CUILabel::SetContainer(int x, int y, int w, int h)
{
	container = {x, y, w, h};
	PreRender();
}

void CUILabel::SetFontSize(int fontSize)
{
	this->fontSize = fontSize;
	SetFont(fontName);
}

void CUILabel::SetVisibility(bool visible)
{
	this->visible = visible;
}

SDL_Rect CUILabel::GetRectangle()
{
	return dstrect;
}

void CUILabel::SetTag(std::string tag)
{
}

std::string CUILabel::GetTag()
{
	return std::string();
}

void CUILabel::ToggleVisibility()
{
	visible = !visible;
}

void CUILabel::PreRender()
{
	if (texture != nullptr)
	{
		SDL_DestroyTexture(texture);
	}

	SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), {255, 255, 255});
	texture = SDL_CreateTextureFromSurface(engine->renderer, surface);

	SDL_QueryTexture(texture, NULL, NULL, &srcrect.w, &srcrect.h);

	int x = 0;
	int y = 0;

	int wOffset = engine->windowWidth;
	int hOffset = engine->windowHeight;
	int xOffset = 0;
	int yOffset = 0;

	if (container.w != 0 || container.h != 0 || container.x != 0 || container.y != 0)
	{
		wOffset = container.w;
		hOffset = container.h;
		xOffset = container.x;
		yOffset = container.y;
	}

	switch (horizontalAlignment)
	{
	case EUIALignmentHorizontal::LEFT:
		x = xOffset + xPos;
		break;
	case EUIALignmentHorizontal::CENTER:
		x = (wOffset / 2) - (srcrect.w / 2) + xOffset + xPos;
		break;
	case EUIALignmentHorizontal::RIGHT:
		x = wOffset - srcrect.w + xPos + xOffset;
		break;
	}

	switch (verticalAlignment)
	{
	case EUIALignmentVertical::TOP:
		y = yOffset + yPos;
		break;
	case EUIALignmentVertical::CENTER:
		y = (hOffset / 2) - (srcrect.h / 2) + yOffset + yPos;
		break;
	case EUIALignmentVertical::BOTTOM:
		y = hOffset - srcrect.h + yPos + yOffset;
		break;
	}

	dstrect = {x, y, srcrect.w, srcrect.h};
	UIdstrect = dstrect;

	SDL_FreeSurface(surface);
}

std::string CUILabel::GetText()
{
	return text;
}

bool CUILabel::GetVisibility()
{
	return visible;
}
