#include "CEntityFinished.h"
#include "CDrawManager.h"
#include "CMap.h"
#include "EUIAlignment.h"


CEntityFinished::CEntityFinished(CEngine* engine) : CEntity(engine), IInputListener(engine)
{
	label = new CUILabel(engine, "Bangers", "");
	label->SetPosition(0, 0);
	label->SetHorizontalAlignment(EUIALignmentHorizontal::CENTER);
	label->SetVerticalAlignment(EUIALignmentVertical::CENTER);
	label->SetFontSize(52);
	label->SetVisibility(true);
	this->engine = engine;
}

CEntityFinished::~CEntityFinished()
{
}

void CEntityFinished::Update()
{
	if (this->car->isFinished)
	{
		label->SetText("FINISHED");
	}
}

void CEntityFinished::Input(SDL_Event* event)
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

void CEntityFinished::SetCamera(CCamera* camera)
{
	this->camera = camera;
	UpdateContainers();
}

void CEntityFinished::SetCar(CEntityCar * car)
{
	this->car = car;
}

void CEntityFinished::UpdateContainers()
{
	label->SetContainer(camera->GetViewPort().x, camera->GetViewPort().y, camera->GetViewPort().w, camera->GetViewPort().h);
}
