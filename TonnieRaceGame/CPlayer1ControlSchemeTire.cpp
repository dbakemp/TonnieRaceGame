#include "CPlayer1ControlSchemeTire.h"
#include "CDeltaHelper.h"
#include "IInputListener.h"

CPlayer1ControlSchemeTire::CPlayer1ControlSchemeTire(CEngine* engine)
{
	this->engine = engine;
}

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
	UpdateFriction();
	UpdateDrive();
	UpdateTurn();
}

void CPlayer1ControlSchemeTire::SetCar(CEntityCar* car)
{
}

void CPlayer1ControlSchemeTire::SetTire(CEntityTire* tire)
{
	this->tire = tire;
}

void CPlayer1ControlSchemeTire::UpdateFriction()
{
	float maxLateralImpulse = engine->deltaHelper->GetScaledDelta() * 1000;
	b2Vec2 impulse = tire->body->GetMass() * -tire->GetLateralVelocity();
	if (impulse.Length() > maxLateralImpulse)
		impulse *= maxLateralImpulse / impulse.Length();
	tire->body->ApplyLinearImpulse(impulse, tire->body->GetWorldCenter(), true);

	tire->body->ApplyAngularImpulse(0.1f * tire->body->GetInertia() * -tire->body->GetAngularVelocity(), true);

	b2Vec2 currentForwardNormal = tire->GetForwardVelocity();
	float currentForwardSpeed = currentForwardNormal.Normalize();
	float dragForceMagnitude = -3 * currentForwardSpeed;
	tire->body->ApplyForce(dragForceMagnitude * currentForwardNormal, tire->body->GetWorldCenter(), true);
}

void CPlayer1ControlSchemeTire::UpdateDrive()
{
	if (tire->powerupActive && tire->type == 0)
	{
		tire->maxDriveForce = 500;
	}
	else
	{
		tire->maxDriveForce = 400;
	}

	float desiredSpeed = 0;
	switch (tire->controlState)
	{
	case IInputListener::InputDirections::UP: desiredSpeed = tire->maxForwardSpeed;
		break;
	case IInputListener::InputDirections::DOWN: desiredSpeed = tire->maxBackwardsSpeed;
		break;
	default: return;
	}

	b2Vec2 currentForwardNormal = tire->body->GetWorldVector(b2Vec2(0, 1));
	float currentSpeed = b2Dot(tire->GetForwardVelocity(), currentForwardNormal);

	float force = 0;
	if (desiredSpeed > currentSpeed)
	{
		force = tire->maxDriveForce;
	}
	else if (desiredSpeed < currentSpeed)
	{
		force -= tire->maxDriveForce;
	}
	else
	{
		return;
	}

	tire->body->ApplyForce(force * currentForwardNormal, tire->body->GetWorldCenter(), true);
}

void CPlayer1ControlSchemeTire::UpdateTurn()
{
	float desiredTorque = 0;
	switch (tire->controlState)
	{
	case IInputListener::InputDirections::UP: desiredTorque = 15;
		break;
	case IInputListener::InputDirections::DOWN: desiredTorque = -15;
		break;
	default: return;
	}

	tire->body->ApplyTorque(desiredTorque, true);
}

void CPlayer1ControlSchemeTire::FinishCallback()
{
}

IControlScheme* CPlayer1ControlSchemeTire::GetNewTireScheme()
{
	return nullptr;
}
