#include "CAIControlSchemeTire.h"
#include "CDeltaHelper.h"

CAIControlSchemeTire::CAIControlSchemeTire(CEngine* engine)
{
	this->engine = engine;
}

void CAIControlSchemeTire::Input(SDL_Event* event)
{
}

void CAIControlSchemeTire::Update()
{
	UpdateFriction();
	UpdateDrive();
	UpdateTurn();
}

void CAIControlSchemeTire::SetCar(CEntityCar* car)
{
}

void CAIControlSchemeTire::SetTire(CEntityTire* tire)
{
	this->tire = tire;
}

void CAIControlSchemeTire::UpdateFriction()
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

void CAIControlSchemeTire::UpdateDrive()
{
	if (tire->powerupActive && tire->type == CEntityPowerup::PowerupType::SPEED)
	{
		tire->maxDriveForce = 900;
	}
	else
	{
		tire->maxDriveForce = 500;
	}

	float desiredSpeed = 0;
	desiredSpeed = tire->maxForwardSpeed;

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

void CAIControlSchemeTire::UpdateTurn()
{
	tire->body->ApplyTorque(15, true);
}

void CAIControlSchemeTire::FinishCallback()
{
}

IControlScheme* CAIControlSchemeTire::GetNewTireScheme()
{
	return nullptr;
}
