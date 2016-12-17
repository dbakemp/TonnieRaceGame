#include "CUIHorizontalScrollView.h"
#include "CDrawManager.h"

CUIHorizontalScrollView::CUIHorizontalScrollView(CEngine* engine) : CEntity(engine), IInputListener(engine), IDrawListener(engine, (int)CDrawManager::Layers::UI)
{
	elementContainer = new CUIContainer(engine);
	elementContainer->SetContainer(dstrect.x, dstrect.y, dstrect.w, dstrect.h);

	this->currentSelectedEntity = nullptr;
	this->currentSelectedEntityIndex = 0;
	this->container = {0, 0, 0, 0};
	this->engine = engine;
	this->scrollAmount = 0;
}

CUIHorizontalScrollView::~CUIHorizontalScrollView()
{
	elementContainer = nullptr;
	containerElements.clear();
}

void CUIHorizontalScrollView::Draw(SDL_Renderer* renderer)
{
	if (!debugVisible) { return; }
	SDL_RenderDrawRect(renderer, &dstrect);
}

void CUIHorizontalScrollView::Update()
{
	if(scrollAmount != toScrollAmount)
	{
		if(scrollAmount < toScrollAmount)
		{
			int scroll = 6;
			if(toScrollAmount - scrollAmount < scroll)
			{
				scroll = toScrollAmount - scrollAmount;
			}
			Scroll(-scroll);
		} else
		{
			int scroll = 6;
			if (scrollAmount - toScrollAmount < scroll)
			{
				scroll =  toScrollAmount - toScrollAmount;
			}
			Scroll(scroll);
		}
	}
}

void CUIHorizontalScrollView::Input(SDL_Event* event)
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

void CUIHorizontalScrollView::SetPosition(int x, int y)
{
	this->xPos = x;
	this->yPos = y;
	this->UIXPos = this->xPos;
	this->UIYPos = this->yPos;
	PreRender();
}

void CUIHorizontalScrollView::SetHorizontalAlignment(EUIALignmentHorizontal alignment)
{
	horizontalAlignment = alignment;
	PreRender();
}

void CUIHorizontalScrollView::SetVerticalAlignment(EUIALignmentVertical alignment)
{
	verticalAlignment = alignment;
	PreRender();
}

void CUIHorizontalScrollView::SetContainer(int x, int y, int w, int h)
{
	container = {x, y, w, h};
	PreRender();
}

void CUIHorizontalScrollView::SetWidth(int width)
{
	srcrect.w = width;
	elementContainer->SetWidth(width);
	PreRender();
}

void CUIHorizontalScrollView::SetHeight(int height)
{
	srcrect.h = height;
	elementContainer->SetHeight(height);
	PreRender();
}

void CUIHorizontalScrollView::Scroll(int scroll)
{
	scrollAmount -= scroll;

	for (IUIEntity* element : containerElements)
	{
		element->SetPosition(element->UIXPos += scroll, element->UIYPos);
	}
}

SDL_Rect CUIHorizontalScrollView::GetRectangle()
{
	return dstrect;
}

void CUIHorizontalScrollView::SetTag(std::string tag)
{
}

std::string CUIHorizontalScrollView::GetTag()
{
	return std::string();
}

void CUIHorizontalScrollView::ScrollToNext()
{
	if (currentSelectedEntityIndex >= containerElements.size() - 1) { return; }

	IUIEntity* entity = containerElements.at(currentSelectedEntityIndex+1);
	int realX = entity->UIdstrect.x + entity->UIdstrect.w / 2;

	realX -= currentSelectedEntity->UIdstrect.x + currentSelectedEntity->UIdstrect.w / 2;

	toScrollAmount += realX;

	currentSelectedEntity = entity;
	currentSelectedEntityIndex++;
}

void CUIHorizontalScrollView::ScrollToPrevious()
{
	if (currentSelectedEntityIndex <= 0) { return; }

	IUIEntity* entity = containerElements.at(currentSelectedEntityIndex - 1);
	int realX = entity->UIdstrect.x + entity->UIdstrect.w / 2;

	realX -= currentSelectedEntity->UIdstrect.x + currentSelectedEntity->UIdstrect.w / 2;

	toScrollAmount += realX;

	currentSelectedEntity = entity;
	currentSelectedEntityIndex--;
}

void CUIHorizontalScrollView::AddUIElement(IUIEntity* element)
{
	if (currentSelectedEntity == nullptr)
	{
		currentSelectedEntity = element;
	}

	int xOffset = element->UIXPos;
	for (IUIEntity* element : containerElements)
	{
		xOffset += element->UIdstrect.w + 20;
	}
	element->SetPosition(xOffset, element->UIYPos);

	containerElements.push_back(element);
	elementContainer->AddUIElement(element);
	PreRender();
}

void CUIHorizontalScrollView::PreRender()
{
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

	elementContainer->SetContainer(dstrect.x, dstrect.y, dstrect.w, dstrect.h);
}
