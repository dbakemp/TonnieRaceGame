#include "CEntityScoreboard.h"
#include "CDrawManager.h"
#include "CMap.h"
#include "EUIAlignment.h"
#include "CMap.h"
#include "CUIContainer.h"
#include "CTimerHelper.h"
#include "CDebugLogger.h"
#include "CEngine.h"
#include "CProfileManager.h"
#include "HighscoresHelper.h"
#include "CTimerHelper.h"

CEntityScoreboard::CEntityScoreboard(CEngine* engine) : CEntity(engine), IInputListener(engine)
{
	image = new CUIImage(engine);
	image->SetPosition(0, 0);
	image->SetHorizontalAlignment(EUIALignmentHorizontal::CENTER);
	image->SetVerticalAlignment(EUIALignmentVertical::CENTER);
	image->ChangeZIndex(image->zIndex+1);
	showing = false;

	leftImage = new CUIImage(engine);
	leftImage->SetPosition(-450, -200);
	leftImage->SetHorizontalAlignment(EUIALignmentHorizontal::CENTER);
	leftImage->SetVerticalAlignment(EUIALignmentVertical::CENTER);
	leftImage->ChangeZIndex(image->zIndex + 1);

	rightImage = new CUIImage(engine);
	rightImage->SetPosition(450, -200);
	rightImage->SetHorizontalAlignment(EUIALignmentHorizontal::CENTER);
	rightImage->SetVerticalAlignment(EUIALignmentVertical::CENTER);
	rightImage->ChangeZIndex(image->zIndex + 1);

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

		if (cars[0]->finishTime == engine->currentMap->allCars[0]->finishTime)
		{
			engine->profileManager->currentProfile->unlockNextLevel();
			engine->profileManager->saveProfile();
		}

		HighscoresHelper* h = new HighscoresHelper();
		CTimerHelper* t = new CTimerHelper();
		h->addHighScore(engine->profileManager->currentProfile->name, t->IntToString(cars[0]->finishTime), 1);
	}

	if (showing) {
		for (int i = 0; i < engine->currentMap->allCars.size(); i++) 
		{
			if (engine->currentMap->allCars[i]->finishTime != INT_MAX) {
				
				std::string title = "";
				if (cars[0]->finishTime == engine->currentMap->allCars[i]->finishTime)
				{ 
					//title = "P1: ";
					title = engine->profileManager->currentProfile->name + ": ";
				}
				else if (cars.size() == 2 && cars[1]->finishTime == engine->currentMap->allCars[i]->finishTime)
				{
					title = "P2: ";
				}
				else
				{
					title = "AI: ";
				}

				labels[i]->SetText(title + engine->timerHelper->IntToString(engine->currentMap->allCars[i]->finishTime));

			}

			if (cars[0]->finishTime == engine->currentMap->allCars[0]->finishTime)
			{
				leftImage->SetImage("Images/gewonnen-left.png");
			}
			else
			{
				leftImage->SetImage("Images/verloren-left.png");
			}


			if (cars.size() == 2)
			{
				if (cars[1]->finishTime == engine->currentMap->allCars[0]->finishTime)
				{
					rightImage->SetImage("Images/gewonnen-right.png");
				}
				else
				{
					rightImage->SetImage("Images/verloren-right.png");
				}
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
