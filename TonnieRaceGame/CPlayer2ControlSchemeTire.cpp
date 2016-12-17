#include "CPlayer2ControlSchemeTire.h"

void CPlayer2ControlSchemeTire::Input(SDL_Event* event)
{
	switch (event->type)
	{
	case SDL_KEYDOWN:
		switch (event->key.keysym.sym)
		{
		case SDLK_UP: tire->controlState |= IInputListener::InputDirections::UP;
			break;
		case SDLK_DOWN: tire->controlState |= IInputListener::InputDirections::DOWN;
			break;
		}
		break;
	case SDL_KEYUP:
		switch (event->key.keysym.sym)
		{
		case SDLK_UP: tire->controlState &= ~IInputListener::InputDirections::UP;
			break;
		case SDLK_DOWN: tire->controlState &= ~IInputListener::InputDirections::DOWN;
			break;
		}
		break;
	case SDL_CONTROLLERBUTTONDOWN:
	case SDL_CONTROLLERBUTTONUP:
		tire->OnControllerButton(event->cbutton);
		break;
	}
}

void CPlayer2ControlSchemeTire::Update()
{
}

void CPlayer2ControlSchemeTire::SetCar(CEntityCar* car)
{
}

void CPlayer2ControlSchemeTire::SetTire(CEntityTire* tire)
{
	this->tire = tire;
}

IControlScheme* CPlayer2ControlSchemeTire::GetNewTireScheme()
{
	return nullptr;
}
