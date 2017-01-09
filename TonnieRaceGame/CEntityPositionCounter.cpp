#include "CEntityPositionCounter.h"
#include "CDrawManager.h"
#include "CMap.h"
#include "EUIAlignment.h"

CEntityPositionCounter::CEntityPositionCounter(CEngine* engine) : CEntity(engine), IInputListener(engine)
{
	label = new CUILabel(engine, "Bangers", "");
	label->SetPosition(-10, 0);
	label->SetHorizontalAlignment(EUIALignmentHorizontal::RIGHT);
	label->SetVerticalAlignment(EUIALignmentVertical::BOTTOM);
	label->SetFontSize(50);

	this->engine = engine;
}

CEntityPositionCounter::~CEntityPositionCounter()
{
}

void CEntityPositionCounter::Update()
{
	if (!car->isFinished)
	{
		label->SetText(std::to_string(car->GetPosition()) + "/" + std::to_string(engine->currentMap->cars.size()));
	}
	else
	{
		label->SetText("");
	}
	
}

void CEntityPositionCounter::Input(SDL_Event* event)
{
	if (event->type == SDL_WINDOWEVENT)
	{
		switch (event->window.event)
		{
		case SDL_WINDOWEVENT_RESIZED:
			UpdateContainers();
			break;
		}
	}
}

void CEntityPositionCounter::SetCar(CEntityCar* car)
{
	this->car = car;
}

void CEntityPositionCounter::SetCamera(CCamera* camera)
{
	this->camera = camera;
	UpdateContainers();
}

void CEntityPositionCounter::UpdateContainers()
{
	label->SetContainer(camera->GetViewPort().x, camera->GetViewPort().y, camera->GetViewPort().w, camera->GetViewPort().h);
}
