#include "CPlayer1ControlSchemeCar.h"
#include "CDebugLogger.h"
#include "CEntityTire.h"
#include "CEntityCar.h"
#include "IInputListener.h"
#include "CPlayer1ControlSchemeTire.h"

void CPlayer1ControlSchemeCar::Input(SDL_Event* event)
{
	switch (event->type)
	{
	case SDL_KEYDOWN:
		switch (event->key.keysym.sym)
		{
		case SDLK_a: car->controlState |= IInputListener::InputDirections::LEFT;
			break;
		case SDLK_d: car->controlState |= IInputListener::InputDirections::RIGHT;
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
		case SDLK_a: car->controlState &= ~IInputListener::InputDirections::LEFT;
			break;
		case SDLK_d: car->controlState &= ~IInputListener::InputDirections::RIGHT;
			break;
		}
		break;
	case SDL_CONTROLLERAXISMOTION:
		car->OnControllerAxis(event->caxis);
		break;
		break;
	}
}

void CPlayer1ControlSchemeCar::Update()
{
}

void CPlayer1ControlSchemeCar::SetCar(CEntityCar* car)
{
	this->car = car;
}

void CPlayer1ControlSchemeCar::SetTire(CEntityTire* tire)
{
}

IControlScheme* CPlayer1ControlSchemeCar::GetNewTireScheme()
{
	return new CPlayer1ControlSchemeTire();
}
