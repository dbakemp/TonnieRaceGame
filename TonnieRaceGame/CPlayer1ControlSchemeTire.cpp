#include "CPlayer1ControlSchemeTire.h"

void CPlayer1ControlSchemeTire::Input(SDL_Event* event)
{
	switch (event->type)
	{
	case SDL_KEYDOWN:
		switch (event->key.keysym.sym)
		{
		case SDLK_w: tire->controlState |= IInputListener::InputDirections::UP;
			break;
		case SDLK_s: tire->controlState |= IInputListener::InputDirections::DOWN;
			break;
		}
		break;
	case SDL_KEYUP:
		switch (event->key.keysym.sym)
		{
		case SDLK_w: tire->controlState &= ~IInputListener::InputDirections::UP;
			break;
		case SDLK_s: tire->controlState &= ~IInputListener::InputDirections::DOWN;
			break;
		}
		break;
	case SDL_CONTROLLERBUTTONDOWN:
	case SDL_CONTROLLERBUTTONUP:
		tire->OnControllerButton(event->cbutton);
		break;
	}
}

void CPlayer1ControlSchemeTire::Update()
{
}

void CPlayer1ControlSchemeTire::SetCar(CEntityCar* car)
{
}

void CPlayer1ControlSchemeTire::SetTire(CEntityTire* tire)
{
	this->tire = tire;
}

IControlScheme* CPlayer1ControlSchemeTire::GetNewTireScheme()
{
	return nullptr;
}
