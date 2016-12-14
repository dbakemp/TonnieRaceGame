#include "CUIContainer.h"
#include "CDrawManager.h"

CUIContainer::CUIContainer(CEngine * engine) : CEntity(engine), IInputListener(engine), IDrawListener(engine, (int)CDrawManager::Layers::UI)
{
	this->container = { 0, 0, 0, 0 };
	this->engine = engine;
}

CUIContainer::~CUIContainer()
{
}

void CUIContainer::Draw(SDL_Renderer * renderer)
{
	if (!debugVisible) { return; }
	SDL_RenderDrawRect(engine->renderer, &dstrect);
}

void CUIContainer::Update()
{
}

void CUIContainer::Input(SDL_Event * event)
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

void CUIContainer::SetPosition(int x, int y)
{
	this->xPos = x;
	this->yPos = y;
	PreRender();
}

void CUIContainer::SetHorizontalAlignment(EUIALignmentHorizontal alignment)
{
	horizontalAlignment = alignment;
	PreRender();
}

void CUIContainer::SetVerticalAlignment(EUIALignmentVertical alignment)
{
	verticalAlignment = alignment;
	PreRender();
}

void CUIContainer::SetContainer(int x, int y, int w, int h)
{
	container = { x, y, w, h };
	PreRender();
}

void CUIContainer::SetWidth(int width)
{
	srcrect.w = width;
	PreRender();
}

void CUIContainer::SetHeight(int height)
{
	srcrect.h = height;
	PreRender();
}

void CUIContainer::AddUIElement(IUIEntity * element)
{
	uiElements.push_back(element);
	element->SetContainer(dstrect.x, dstrect.y, dstrect.w, dstrect.h);
}

void CUIContainer::PreRender()
{
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

	for (IUIEntity* element : uiElements) {
		element->SetContainer(dstrect.x, dstrect.y, dstrect.w, dstrect.h);
	}
}
