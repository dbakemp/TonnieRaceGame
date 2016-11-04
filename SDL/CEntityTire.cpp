#include "CEntityTire.h"
#include "Box2DUtils.h" 

CEntityTire::CEntityTire(CEngine * engine) : CEntity(engine), IDrawListener(engine), IInputListener(engine), IBox2DListener(engine)
{
	bodyDef.type = b2_dynamicBody;
	body = engine->world->CreateBody(&bodyDef);

	polygon.SetAsBox(0.75f, 1.25f);
	body->CreateFixture(&polygon, 1);

	body->SetUserData(this);

	maxForwardSpeed = 500;
	maxBackwardsSpeed = -40;
	maxDriveForce = 550;

	this->engine = engine;
}

void CEntityTire::Draw(SDL_Renderer * renderer)
{
	Box2DUtils::DrawBody(renderer, body, engine->camera, 0, 0, 255, 255, 0, 0, 255, 255, false);
}

void CEntityTire::Input(SDL_Event * event)
{
	switch (event->type) {
	case SDL_KEYDOWN:
		switch(event->key.keysym.sym) {
			case SDLK_w: controlState |= InputDirections::UP; break;
			case SDLK_s: controlState |= InputDirections::DOWN; break;
		}
		break;
	case SDL_KEYUP:
		switch (event->key.keysym.sym) {
			case SDLK_w: controlState &= ~InputDirections::UP; break;
			case SDLK_s: controlState &= ~InputDirections::DOWN; break;
		}
		break;
	}
}

void CEntityTire::Update()
{
	UpdateFriction();
	UpdateDrive();
	UpdateTurn();
}

void CEntityTire::Create(b2World * world)
{
}

void CEntityTire::UpdateFriction()
{
	float maxLateralImpulse = 6.0f;
	b2Vec2 impulse = body->GetMass() * -GetLateralVelocity();
	if (impulse.Length() > maxLateralImpulse)
		impulse *= maxLateralImpulse / impulse.Length();
	body->ApplyLinearImpulse(impulse, body->GetWorldCenter(), true);

	body->ApplyAngularImpulse(0.1f * body->GetInertia() * -body->GetAngularVelocity(), true);

	b2Vec2 currentForwardNormal = GetForwardVelocity();
	float currentForwardSpeed = currentForwardNormal.Normalize();
	float dragForceMagnitude = -5 * currentForwardSpeed;
	body->ApplyForce(dragForceMagnitude * currentForwardNormal, body->GetWorldCenter(), true);
}

void CEntityTire::UpdateDrive()
{
	float desiredSpeed = 0;
	switch (controlState) {
		case InputDirections::UP: desiredSpeed = maxForwardSpeed; break;
		case InputDirections::DOWN: desiredSpeed = maxBackwardsSpeed; break;
		default: return;
	}
	
	b2Vec2 currentForwardNormal = body->GetWorldVector(b2Vec2(0, 1));
	float currentSpeed = b2Dot(GetForwardVelocity(), currentForwardNormal);

	float force = 0;
	if (desiredSpeed > currentSpeed) {
		force = maxDriveForce;
	}
	else if (desiredSpeed < currentSpeed) {
		force -= maxDriveForce;
	}
	else {
		return;
	}

	body->ApplyForce(force*currentForwardNormal, body->GetWorldCenter(), true);
}

void CEntityTire::UpdateTurn()
{
	float desiredTorque = 0;
	switch (controlState) {
		case InputDirections::UP: desiredTorque = 15; break;
		case InputDirections::DOWN: desiredTorque = -15; break;
		default: return;
	}

	body->ApplyTorque(desiredTorque, true);
}

b2Vec2 CEntityTire::GetLateralVelocity()
{
	b2Vec2 currentRightNormal = body->GetWorldVector(b2Vec2(1, 0));
	return b2Dot(currentRightNormal, body->GetLinearVelocity())*currentRightNormal;
}

b2Vec2 CEntityTire::GetForwardVelocity()
{
	b2Vec2 currentForwardNormal = body->GetWorldVector(b2Vec2(0, 1));
	return b2Dot(currentForwardNormal, body->GetLinearVelocity())*currentForwardNormal;
}
