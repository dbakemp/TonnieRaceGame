#include "CUIImage.h"
#include "CDrawManager.h"
#include "EUIAlignment.h"
#include "SDL_image.h"
#include "CTextureManager.h"

CUIImage::CUIImage(CEngine * engine) : CEntity(engine), IInputListener(engine), IDrawListener(engine, (int)CDrawManager::Layers::UI)
{
	this->engine = engine;
	this->container = { 0, 0, 0, 0 };
	this->clickCallback = nullptr;
	this->clickCallHoldback = nullptr;

	horizontalAlignment = EUIALignmentHorizontal::LEFT;
	verticalAlignment = EUIALignmentVertical::TOP;
	horizontalStretch = EUIStretchHorizontal::NONE;
	verticalStretch = EUIStretchVertical::NONE;
}

CUIImage::CUIImage(CEngine * engine, std::string texture) : CEntity(engine), IInputListener(engine), IDrawListener(engine, (int)CDrawManager::Layers::UI)
{
	this->engine = engine;

	this->texture = engine->textureManager->GetTexture(texture);

	this->container = { 0, 0, 0, 0 };
	this->clickCallback = nullptr;
	this->clickCallHoldback = nullptr;

	horizontalAlignment = EUIALignmentHorizontal::LEFT;
	verticalAlignment = EUIALignmentVertical::TOP;
	horizontalStretch = EUIStretchHorizontal::NONE;
	verticalStretch = EUIStretchVertical::NONE;
}

CUIImage::~CUIImage()
{
}

void CUIImage::Draw(SDL_Renderer * renderer)
{
	if (container.x == 0 && container.y == 0 && container.w == 0 && container.h == 0) {
		SDL_RenderCopy(engine->renderer, texture, NULL, &dstrect);
	}
	else {
		SDL_QueryTexture(texture, NULL, NULL, &srcrect.w, &srcrect.h);
		int originalWidth = srcrect.w;
		int totalWidthRight = container.w + container.x - dstrect.x;
		int totalWidthLeft = container.x - dstrect.x;

		if (totalWidthRight > 0 && totalWidthRight <= dstrect.w) {
			srcrect.w = totalWidthRight;
			dstrect.w = srcrect.w;

			SDL_RenderCopy(engine->renderer, texture, &srcrect, &dstrect);
		}
		else if (totalWidthLeft > 0 && totalWidthLeft <= dstrect.w) {
			srcrect.x = totalWidthLeft;
			dstrect.x = dstrect.x + totalWidthLeft;
			dstrect.w = srcrect.w - totalWidthLeft;

			SDL_RenderCopy(engine->renderer, texture, &srcrect, &dstrect);
		}
		else if (dstrect.x + originalWidth > container.x && dstrect.x < container.w + container.x) {
			SDL_RenderCopy(engine->renderer, texture, &srcrect, &dstrect);
		}
	}

	if (!debugVisible) { return; }
	SDL_RenderDrawRect(engine->renderer, &dstrect);
}

void CUIImage::Update()
{
	if (mouseDown) {
		if (clickCallHoldback != nullptr) { clickCallHoldback(this); }
	}
}

void CUIImage::Input(SDL_Event * event)
{
	if (event->type == SDL_MOUSEBUTTONDOWN) {
		if ((event->motion.x > dstrect.x && event->motion.x < dstrect.x + dstrect.w) && (event->motion.y > dstrect.y && event->motion.y < dstrect.y + dstrect.h)) {
			mouseDown = true;
		}
	}
	else if (event->type == SDL_MOUSEBUTTONUP) {
		if (mouseDown) {
			if (clickCallback != nullptr) { clickCallback(this); }
			mouseDown = false;
		}
	} else if (event->type == SDL_WINDOWEVENT) {
		switch (event->window.event) {
		case SDL_WINDOWEVENT_RESIZED:
			PreRender();
			break;
		}
	}
	else if (event->type == SDL_KEYDOWN) {

		switch (event->key.keysym.sym)
		{
		case SDLK_f:
			debugVisible = !debugVisible;
			break;
		}
	}
}

void CUIImage::SetPosition(int x, int y)
{
	this->xPos = x;
	this->yPos = y;
	this->UIXPos = this->xPos;
	this->UIYPos = this->yPos;
	PreRender();
}

void CUIImage::SetHorizontalAlignment(EUIALignmentHorizontal alignment)
{
	horizontalAlignment = alignment;
	PreRender();
}

void CUIImage::SetVerticalAlignment(EUIALignmentVertical alignment)
{
	verticalAlignment = alignment;
	PreRender();
}

void CUIImage::SetHorizontalStretch(EUIStretchHorizontal stretch)
{
	horizontalStretch = stretch;
	PreRender();
}

void CUIImage::SetVerticalStretch(EUIStretchVertical stretch)
{
	verticalStretch = stretch;
	PreRender();
}

void CUIImage::SetContainer(int x, int y, int w, int h)
{
	container = { x, y, w, h };
	PreRender();
}

void CUIImage::SetTag(std::string tag)
{
	this->tag = tag;
}

void CUIImage::SetClickCallback(std::function<void(IUIEntity*)> callback)
{
	this->clickCallback = callback;
}

void CUIImage::SetClickHoldCallback(std::function<void(IUIEntity*)> callback)
{
	this->clickCallHoldback = callback;
}

std::string CUIImage::GetTag()
{
	return tag;
}

void CUIImage::PreRender()
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

	switch (horizontalStretch) {
		case EUIStretchHorizontal::FIT:
			double scale = wOffset / srcrect.w;
			srcrect.w = wOffset;
			srcrect.h = (int)(srcrect.h*scale);
			break;
	}

	switch (verticalStretch) {
	case EUIStretchVertical::FIT:
		double scale = (double)hOffset / (double)srcrect.h;
		srcrect.h = hOffset;
		srcrect.w = (int)(srcrect.w*scale);
		break;
	}

	switch (horizontalAlignment) {
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

	switch (verticalAlignment) {
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

	dstrect = { x, y, srcrect.w, srcrect.h };
	UIdstrect = dstrect;
}
