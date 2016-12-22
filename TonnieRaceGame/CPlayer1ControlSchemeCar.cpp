#include "CPlayer1ControlSchemeCar.h"
#include "CDebugLogger.h"
#include "CEntityTire.h"
#include "CEntityCar.h"
#include "IInputListener.h"
#include "CPlayer1ControlSchemeTire.h"
#include "CDeltaHelper.h"
#include "CAIControlSchemeCar.h"

#ifndef DEGTORAD
#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
#endif

CPlayer1ControlSchemeCar::CPlayer1ControlSchemeCar(CEngine* engine)
{
	this->engine = engine;
}

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
			if (car->activePowerup != CEntityPowerup::PowerupType::NONE && !car->powerupActive)
			{
				car->powerupActive = true;
				for (CEntityTire* tire : car->tires)
				{
					tire->powerupActive = true;
					tire->type = static_cast<int>(car->activePowerup);
				}
				CDebugLogger::PrintDebug("Powerup geactiveerd");
			}
			break;
		case SDLK_F5:
			//Powerup1 oppakken
			CDebugLogger::PrintDebug("CHEAT: Powerup speed oppakken");
			car->activePowerup = CEntityPowerup::PowerupType::SPEED;
			break;
		case SDLK_F6:
			//Powerup2 oppakken
			CDebugLogger::PrintDebug("CHEAT: Powerup dronken oppakken");
			car->activePowerup = CEntityPowerup::PowerupType::DRUNK;
			break;
		case SDLK_F2:
			//Laatste lap van level
			CDebugLogger::PrintDebug("CHEAT: Laatste lap van level");
			car->currentLap = engine->currentMap->laps - 1;
			break;
		case SDLK_F3:
			//Level afronden(winnen)
			CDebugLogger::PrintDebug("CHEAT: Level afronden (winnen)");
			car->currentLap = engine->currentMap->laps - 1;
			car->FinishCallback();
			break;
		case SDLK_F4:
			//Level afronden(verliezen)
			CDebugLogger::PrintDebug("CHEAT: Level afronden (verliezen)");
			car->currentLap = engine->currentMap->laps - 1;
			car->FinishCallback();
			break;
		case SDLK_KP_PLUS:
			engine->musicHelper->stopAll();
			engine->musicHelper->playBackgroundMusic();
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

	if (car->powerupActive && car->activePowerup != CEntityPowerup::PowerupType::NONE && static_cast<int>(car->activePowerup) == 1)
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
			car->activePowerup = CEntityPowerup::PowerupType::NONE;
			for (CEntityTire* tire : car->tires)
			{
				tire->powerupActive = false;
			}
		}
	}
	car->emitter->SetPosition(((car->aabb.upperBound.x + car->aabb.lowerBound.x) / 2 * 5), ((car->aabb.upperBound.y + car->aabb.lowerBound.y) / 2 * 5));
}

void CPlayer1ControlSchemeCar::SetCar(CEntityCar* car)
{
	this->car = car;
}

void CPlayer1ControlSchemeCar::SetTire(CEntityTire* tire)
{
}

void CPlayer1ControlSchemeCar::UpdateFriction()
{
}

void CPlayer1ControlSchemeCar::UpdateDrive()
{
}

void CPlayer1ControlSchemeCar::UpdateTurn()
{
}

void CPlayer1ControlSchemeCar::FinishCallback()
{
	car->ChangeWaypoint(engine->currentMap->waypoints[0]);
	car->currentWaypoint = 0;
	this->car->SetControlScheme(new CAIControlSchemeCar(engine));
}

IControlScheme* CPlayer1ControlSchemeCar::GetNewTireScheme()
{
	return new CPlayer1ControlSchemeTire(engine);
}
