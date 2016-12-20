#include "CEntityPowerupHUD.h"
#include "CDrawManager.h"
#include "CMap.h"
#include "EUIAlignment.h"


CEntityPowerupHUD::CEntityPowerupHUD(CEngine* engine) : CEntity(engine), IInputListener(engine)
{
	image = new CUIImage(engine);
	image->SetPosition(383, 0);
	image->SetHorizontalAlignment(EUIALignmentHorizontal::LEFT);
	image->SetVerticalAlignment(EUIALignmentVertical::BOTTOM);
	this->engine = engine;
}

CEntityPowerupHUD::~CEntityPowerupHUD()
{
}

void CEntityPowerupHUD::Update()
{
	if (this->car->activePowerup == nullptr)
	{
		image->SetImage("");
	}

	else if (this->car->activePowerup->type == CEntityPowerup::PowerupType::DRUNK)
	{
		image->SetImage("Images/beerPowerup.png");
	}
	else if (this->car->activePowerup->type == CEntityPowerup::PowerupType::SPEED)
	{
		image->SetImage("Images/speedPowerup.png");
	}
	else
	{
			//Robin is een gaylord
	}
}

void CEntityPowerupHUD::Input(SDL_Event* event)
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

void CEntityPowerupHUD::SetCamera(CCamera* camera)
{
	this->camera = camera;
	UpdateContainers();
}

void CEntityPowerupHUD::SetCar(CEntityCar * car)
{
	this->car = car;
}

void CEntityPowerupHUD::UpdateContainers()
{
	image->SetContainer(camera->GetViewPort().x, camera->GetViewPort().y, camera->GetViewPort().w, camera->GetViewPort().h);
}
