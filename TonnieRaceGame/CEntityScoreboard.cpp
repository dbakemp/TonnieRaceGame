#include "CEntityScoreboard.h"
#include "CDrawManager.h"
#include "CMap.h"
#include "EUIAlignment.h"
#include "CMap.h"
#include "CUIContainer.h"
#include "CTimerHelper.h"

CEntityScoreboard::CEntityScoreboard(CEngine* engine) : CEntity(engine), IInputListener(engine)
{
	image = new CUIImage(engine);
	image->SetPosition(0, 0);
	image->SetHorizontalAlignment(EUIALignmentHorizontal::CENTER);
	image->SetVerticalAlignment(EUIALignmentVertical::CENTER);
	image->ChangeZIndex(image->zIndex+1);
	showing = false;

	container = new CUIContainer(engine);
	container->SetHorizontalAlignment(EUIALignmentHorizontal::CENTER);
	container->SetVerticalAlignment(EUIALignmentVertical::CENTER);
	container->SetHeight(400);
	container->SetWidth(300);
	container->SetPosition(0, 0);

	this->engine = engine;
}

CEntityScoreboard::~CEntityScoreboard()
{
	cars.clear();
}

void CEntityScoreboard::Update()
{
	bool finished = true;

	for (CEntityCar* car : cars) {
		if (!car->isFinished) {
			finished = false;
		}
	}

	if (finished && !showing) {
		image->SetImage("Images/scoreboard.png");

		for (CEntityCar* car : engine->currentMap->cars) {
			CUILabel* label = new CUILabel(engine, "Bangers", "");
			label->SetPosition(0, 70 + (42 * labels.size()));
			label->SetFontSize(40);
			label->SetHorizontalAlignment(EUIALignmentHorizontal::CENTER);
			label->SetVerticalAlignment(EUIALignmentVertical::TOP);
			label->ChangeZIndex(label->zIndex+2);
			container->AddUIElement(label);
			labels.push_back(label);
		}

		showing = true;
	}

	if (showing) {
		for (int i = 0; i < engine->currentMap->allCars.size(); i++) {
			if (engine->currentMap->allCars[i]->finishTime != 0) {
				labels[i]->SetText(engine->timerHelper->IntToString(engine->currentMap->allCars[i]->finishTime));
			}
		}
	}

}

void CEntityScoreboard::Input(SDL_Event* event)
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

void CEntityScoreboard::SetCamera(CCamera* camera)
{
	this->camera = camera;
	UpdateContainers();
}

void CEntityScoreboard::SetCar(CEntityCar * car)
{
	cars.push_back(car);
}

void CEntityScoreboard::UpdateContainers()
{
	image->SetContainer(camera->GetViewPort().x, camera->GetViewPort().y, camera->GetViewPort().w, camera->GetViewPort().h);
	container->SetContainer(camera->GetViewPort().x, camera->GetViewPort().y, camera->GetViewPort().w, camera->GetViewPort().h);
}
