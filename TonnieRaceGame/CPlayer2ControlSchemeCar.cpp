#include "CPlayer2ControlSchemeCar.h"
#include "CDebugLogger.h"
#include "CEntityTire.h"
#include "CEntityCar.h"
#include "IInputListener.h"
#include "CPlayer2ControlSchemeTire.h"

void CPlayer2ControlSchemeCar::Input(SDL_Event* event)
{
	switch (event->type)
	{
	case SDL_KEYDOWN:
		switch (event->key.keysym.sym)
		{
		case SDLK_LEFT: car->controlState |= IInputListener::InputDirections::LEFT;
			break;
		case SDLK_RIGHT: car->controlState |= IInputListener::InputDirections::RIGHT;
			break;
		case SDLK_f:
			car->debugVisible = !car->debugVisible;
			break;
		case SDLK_SPACE:
			if (car->activePowerup != nullptr && !car->powerupActive)
			{
				car->powerupActive = true;
				for (CEntityTire* tire : car->tires)
				{
					tire->powerupActive = true;
					tire->type = static_cast<int>(car->activePowerup->type);
				}
				CDebugLogger::PrintDebug("Powerup geactiveerd");
			}
			break;
		}
		break;
	case SDL_KEYUP:
		switch (event->key.keysym.sym)
		{
		case SDLK_LEFT: car->controlState &= ~IInputListener::InputDirections::LEFT;
			break;
		case SDLK_RIGHT: car->controlState &= ~IInputListener::InputDirections::RIGHT;
			break;
		}
		break;
	case SDL_CONTROLLERAXISMOTION:
		car->OnControllerAxis(event->caxis);
		break;
		break;
	}
}

void CPlayer2ControlSchemeCar::Update()
{
}

void CPlayer2ControlSchemeCar::SetCar(CEntityCar* car)
{
	this->car = car;
}

void CPlayer2ControlSchemeCar::SetTire(CEntityTire* tire)
{
}

IControlScheme* CPlayer2ControlSchemeCar::GetNewTireScheme()
{
	return new CPlayer2ControlSchemeTire();
}
