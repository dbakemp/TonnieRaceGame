#include "CPlayer2ControlSchemeCar.h"
#include "CDebugLogger.h"
#include "CEntityTire.h"
#include "CEntityCar.h"
#include "IInputListener.h"
#include "CPlayer2ControlSchemeTire.h"
#include "CDeltaHelper.h"
#include "CAIControlSchemeCar.h"

#ifndef DEGTORAD
#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
#endif

CPlayer2ControlSchemeCar::CPlayer2ControlSchemeCar(CEngine* engine)
{
	this->engine = engine;
}

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
	//control steering
	double lockAngle = 50 * DEGTORAD;
	double turnSpeedPerSec = 250 * DEGTORAD;
	double turnPerTimeStep = turnSpeedPerSec / (1.0 / engine->deltaHelper->GetScaledDelta());
	double desiredAngle = 0;

	switch (car->controlState)
	{
	case IInputListener::InputDirections::RIGHT: desiredAngle = lockAngle;
		break;
	case IInputListener::InputDirections::LEFT: desiredAngle = -lockAngle;
		break;
	}

	if (car->powerupActive && car->activePowerup != nullptr && static_cast<int>(car->activePowerup->type) == 1)
	{
		desiredAngle = 0 - desiredAngle;
	}

	double angleNow = car->flJoint->GetJointAngle();
	double angleToTurn = desiredAngle - angleNow;
	angleToTurn = b2Clamp(angleToTurn, -turnPerTimeStep, turnPerTimeStep);
	double newAngle = angleNow + (angleToTurn);
	car->flJoint->SetLimits(newAngle, newAngle);
	car->frJoint->SetLimits(newAngle, newAngle);

	if (car->powerupActive)
	{
		car->powerupTimer += engine->deltaHelper->GetScaledDelta();
		if (car->powerupTimer > (rand() % (10 - 5 + 1) + 5))
		{
			CDebugLogger::PrintDebug("Powerup verlopen");
			car->powerupTimer = 0;
			car->powerupActive = false;
			car->activePowerup = nullptr;
			for (CEntityTire* tire : car->tires)
			{
				tire->powerupActive = false;
			}
		}
	}
	car->emitter->SetPosition(((car->aabb.upperBound.x + car->aabb.lowerBound.x) / 2 * 5), ((car->aabb.upperBound.y + car->aabb.lowerBound.y) / 2 * 5));
}

void CPlayer2ControlSchemeCar::SetCar(CEntityCar* car)
{
	this->car = car;
}

void CPlayer2ControlSchemeCar::SetTire(CEntityTire* tire)
{
}

void CPlayer2ControlSchemeCar::UpdateFriction()
{
}

void CPlayer2ControlSchemeCar::UpdateDrive()
{
}

void CPlayer2ControlSchemeCar::UpdateTurn()
{
}

void CPlayer2ControlSchemeCar::FinishCallback()
{
	car->ChangeWaypoint(engine->currentMap->waypoints[0]);
	car->currentWaypoint = 0;
	this->car->SetControlScheme(new CAIControlSchemeCar(engine));
}

IControlScheme* CPlayer2ControlSchemeCar::GetNewTireScheme()
{
	return new CPlayer2ControlSchemeTire(engine);
}
