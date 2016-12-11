#include "CUIImage.h"
#include "CDrawManager.h"
#include "EUIAlignment.h"
#include "SDL_image.h"
#include "CTextureManager.h"

CUIImage::CUIImage(CEngine * engine) : CEntity(engine), IInputListener(engine), IDrawListener(engine, (int)CDrawManager::Layers::UI)
{
	this->engine = engine;
	this->container = { 0, 0, 0, 0 };

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
	SDL_RenderCopy(engine->renderer, texture, NULL, &dstrect);

	if (!debugVisible) { return; }
	SDL_RenderDrawRect(engine->renderer, &dstrect);
}

void CUIImage::Update()
{
}

void CUIImage::Input(SDL_Event * event)
{
	if (event->type == SDL_WINDOWEVENT) {
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
}
