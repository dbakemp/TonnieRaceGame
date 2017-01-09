#include "CAIControlSchemeCar.h"
#include "CDebugLogger.h"
#include "CEntityTire.h"
#include "CEntityCar.h"
#include "IInputListener.h"
#include "CDeltaHelper.h"
#include "CAIControlSchemeTire.h"

#ifndef DEGTORAD
#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
#endif

CAIControlSchemeCar::CAIControlSchemeCar(CEngine* engine)
{
	this->engine = engine;
}

void CAIControlSchemeCar::Input(SDL_Event* event)
{
}

void CAIControlSchemeCar::Update()
{
	if (car->heading == nullptr)
	{
		car->ChangeWaypoint(engine->currentMap->waypoints[car->currentWaypoint + 1]);
		car->currentWaypoint++;
	}

	b2AABB aabb;
	aabb.lowerBound = b2Vec2(FLT_MAX, FLT_MAX);
	aabb.upperBound = b2Vec2(-FLT_MAX, -FLT_MAX);
	b2Fixture* fixture = car->body->GetFixtureList();
	while (fixture != NULL)
	{
		aabb.Combine(aabb, fixture->GetAABB(0));
		fixture = fixture->GetNext();
	}

	b2Vec2 veca = { (aabb.lowerBound.x + aabb.upperBound.x) / 2, (aabb.lowerBound.y + aabb.upperBound.y) / 2 };
	b2Vec2 vecb = car->heading->body->GetPosition();

	double deltaX = veca.x - (vecb.x + car->biasX);
	double deltaY = veca.y - (vecb.y + car->biasY);

	double angle = (atan2(deltaY, deltaX) * 180 / M_PI) + 90.0f;
	if (angle < 270 && angle > 180)
	{
		angle = angle - 360;
	}

	double carAngle = car->body->GetAngle() * 180 / M_PI;
	while (carAngle <= -180)
	{
		carAngle += 360;
	}
	while (carAngle > 180)
	{
		carAngle -= 360;
	}

	double headingAngle;
	headingAngle = carAngle - angle;
	if (headingAngle < -180)
	{
		headingAngle += 360;
	}
	else if (headingAngle > 180)
	{
		headingAngle -= 360;
	}

	//control steering
	double lockAngle = 50 * DEGTORAD;
	double turnSpeedPerSec = 250 * DEGTORAD;
	double turnPerTimeStep = turnSpeedPerSec / (1.0 / engine->deltaHelper->GetScaledDelta());
	double desiredAngle = -headingAngle * DEGTORAD;
	if (desiredAngle < -lockAngle)
	{
		desiredAngle = -lockAngle;
	}
	else if (desiredAngle > lockAngle)
	{
		desiredAngle = lockAngle;
	}

	if (car->shouldBackup)
	{
		desiredAngle = -desiredAngle;
	}

	if (car->powerupActive && car->activePowerup == CEntityPowerup::PowerupType::DRUNK)
	{
		desiredAngle = 0 - desiredAngle;
	}

	double angleNow = car->flJoint->GetJointAngle();
	double angleToTurn = desiredAngle - angleNow;
	angleToTurn = b2Clamp(angleToTurn, -turnPerTimeStep, turnPerTimeStep);
	double newAngle = angleNow + (angleToTurn);
	car->flJoint->SetLimits(newAngle, newAngle);
	car->frJoint->SetLimits(newAngle, newAngle);

	b2Vec2 velocity = car->body->GetLinearVelocity();
	if ((int)(velocity.Normalize()) < 5)
	{
		car->backupTimer += engine->deltaHelper->GetScaledDelta();
	}
	else
	{
		car->backupTimer = 0;
	}

	if (car->backupTimer > 1.5)
	{
		car->shouldBackup = true;
	}


	b2Vec2 vecc = veca - vecb;
	float distance = vecc.Normalize();

	if (desiredAngle < 0)
	{
		desiredAngle = -desiredAngle;
	}

	if (car->shouldBackup && car->backingupTimer < 1)
	{
		car->backingupTimer += engine->deltaHelper->GetScaledDelta();
		for (CEntityTire* tire : car->tires)
		{
			tire->maxForwardSpeed = -65;
		}
	}
	else
	{
		car->shouldBackup = false;
		car->backingupTimer = 0;
		for (CEntityTire* tire : car->tires)
		{
			if (distance > (velocity.Normalize() * 0.8f))
			{
				tire->maxForwardSpeed = 600 - (desiredAngle * 600);
			}
			else
			{
				tire->maxForwardSpeed = 0;
			}
		}
	}

	if (car->powerupActive)
	{
		car->powerupTimer += engine->deltaHelper->GetScaledDelta();
		float time = (rand() % (5 - 2 + 1) + 2);
		if (this->car->activePowerup == CEntityPowerup::PowerupType::SPEED) {
			time = (rand() % (10 - 5 + 1) + 5);
		}
		if (car->powerupTimer > time)
		{
			car->powerupTimer = 0;
			car->powerupActive = false;
			car->activePowerup = CEntityPowerup::PowerupType::NONE;
			for (CEntityTire* tire : car->tires)
			{
				tire->powerupActive = false;
				tire->type = CEntityPowerup::PowerupType::NONE;
			}
		}
	}

	car->emitter->SetPosition(((car->aabb.upperBound.x + car->aabb.lowerBound.x) / 2 * 5), ((car->aabb.upperBound.y + car->aabb.lowerBound.y) / 2 * 5));
}

void CAIControlSchemeCar::SetCar(CEntityCar* car)
{
	this->car = car;
}

void CAIControlSchemeCar::SetTire(CEntityTire* tire)
{
}

void CAIControlSchemeCar::UpdateFriction()
{
}

void CAIControlSchemeCar::UpdateDrive()
{
}

void CAIControlSchemeCar::UpdateTurn()
{
}

void CAIControlSchemeCar::FinishCallback()
{
}

IControlScheme* CAIControlSchemeCar::GetNewTireScheme()
{
	return new CAIControlSchemeTire(engine);
}
