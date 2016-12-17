#include "CEntityLapCounter.h"
#include "CDrawManager.h"
#include "CMap.h"
#include "EUIAlignment.h"

CEntityLapCounter::CEntityLapCounter(CEngine* engine) : CEntity(engine), IInputListener(engine)
{
	label = new CUILabel(engine, "Bangers", "");
	label->SetPosition(-10, 10);
	label->SetHorizontalAlignment(EUIALignmentHorizontal::RIGHT);
	label->SetFontSize(30);

	this->engine = engine;
}

CEntityLapCounter::~CEntityLapCounter()
{
}

void CEntityLapCounter::Update()
{
	label->SetText("Lap:" + std::to_string(lapCountable->currentLap + 1) + "/" + std::to_string(engine->currentMap->laps));
}

void CEntityLapCounter::Input(SDL_Event* event)
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

void CEntityLapCounter::SetLapCountable(ILapCountable* lapCountable)
{
	this->lapCountable = lapCountable;
}

ILapCountable* CEntityLapCounter::GetLapCountable()
{
	return lapCountable;
}

void CEntityLapCounter::SetCamera(CCamera* camera)
{
	this->camera = camera;
	UpdateContainers();
}

void CEntityLapCounter::UpdateContainers()
{
	label->SetContainer(camera->GetViewPort().x, camera->GetViewPort().y, camera->GetViewPort().w, camera->GetViewPort().h);
}
