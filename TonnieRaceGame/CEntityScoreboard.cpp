#include "CEntityScoreboard.h"
#include "CDrawManager.h"
#include "CMap.h"
#include "EUIAlignment.h"


CEntityScoreboard::CEntityScoreboard(CEngine* engine) : CEntity(engine), IInputListener(engine)
{
	image = new CUIImage(engine);
	image->SetPosition(0, 0);
	image->SetHorizontalAlignment(EUIALignmentHorizontal::CENTER);
	image->SetVerticalAlignment(EUIALignmentVertical::CENTER);
	this->engine = engine;
}

CEntityScoreboard::~CEntityScoreboard()
{
}

void CEntityScoreboard::Update()
{
	if (this->car->isFinished)
	{
		image->SetImage("Images/scoreboard.png");
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
	this->car = car;
}

void CEntityScoreboard::UpdateContainers()
{
	image->SetContainer(camera->GetViewPort().x, camera->GetViewPort().y, camera->GetViewPort().w, camera->GetViewPort().h);
}
