#include "CEntityTireAI.h"
#include "Box2DUtils.h" 
#include "CDeltaHelper.h" 
#include "CDrawManager.h" 
#include "CMap.h"
#include <SDL.h>
#include <iostream>

CEntityTireAI::CEntityTireAI(CEngine* engine, CMap* map, int x, int y) : CEntity(engine), IDrawListener(engine, (int)CDrawManager::Layers::Object), IBox2DListener(engine)
{
	double xPos = x;
	double yPos = y;

	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(xPos, yPos);
	body = engine->world->CreateBody(&bodyDef);

	bodyDef.position.Set(xPos, yPos);
	polygon.SetAsBox(0.75f, 1.25f);
	body->CreateFixture(&polygon, 1);
	body->SetUserData(this);

	maxForwardSpeed = 150;
	maxBackwardsSpeed = -40;
	maxDriveForce = 250;

	this->engine = engine;
}

void CEntityTireAI::Draw(SDL_Renderer* renderer)
{
	Box2DUtils::DrawBody(renderer, body, engine->camera, 0, 0, 0, 255, 0, 0, 0, 255, false);
}

void CEntityTireAI::Update()
{
	UpdateFriction();
	UpdateDrive();
	UpdateTurn();
}

void CEntityTireAI::Create(b2World* world)
{
}

void CEntityTireAI::UpdateFriction()
{
	float maxLateralImpulse = engine->deltaHelper->delta * 1000;
	b2Vec2 impulse = body->GetMass() * -GetLateralVelocity();
	if (impulse.Length() > maxLateralImpulse)
		impulse *= maxLateralImpulse / impulse.Length();
	body->ApplyLinearImpulse(impulse, body->GetWorldCenter(), true);

	body->ApplyAngularImpulse(0.1f * body->GetInertia() * -body->GetAngularVelocity(), true);

	b2Vec2 currentForwardNormal = GetForwardVelocity();
	float currentForwardSpeed = currentForwardNormal.Normalize();
	float dragForceMagnitude = -3 * currentForwardSpeed;
	body->ApplyForce(dragForceMagnitude * currentForwardNormal, body->GetWorldCenter(), true);
}

void CEntityTireAI::UpdateDrive()
{
	float desiredSpeed = 0;
	desiredSpeed = maxForwardSpeed;

	b2Vec2 currentForwardNormal = body->GetWorldVector(b2Vec2(0, 1));
	float currentSpeed = b2Dot(GetForwardVelocity(), currentForwardNormal);

	float force = 0;
	if (desiredSpeed > currentSpeed)
	{
		force = maxDriveForce;
	}
	else if (desiredSpeed < currentSpeed)
	{
		force -= maxDriveForce;
	}
	else
	{
		return;
	}

	body->ApplyForce(force * currentForwardNormal, body->GetWorldCenter(), true);
}

void CEntityTireAI::UpdateTurn()
{
	float desiredTorque = 0;
	desiredTorque = 15;

	body->ApplyTorque(desiredTorque, true);
}

b2Vec2 CEntityTireAI::GetLateralVelocity()
{
	b2Vec2 currentRightNormal = body->GetWorldVector(b2Vec2(1, 0));
	return b2Dot(currentRightNormal, body->GetLinearVelocity()) * currentRightNormal;
}

b2Vec2 CEntityTireAI::GetForwardVelocity()
{
	b2Vec2 currentForwardNormal = body->GetWorldVector(b2Vec2(0, 1));
	return b2Dot(currentForwardNormal, body->GetLinearVelocity()) * currentForwardNormal;
}
