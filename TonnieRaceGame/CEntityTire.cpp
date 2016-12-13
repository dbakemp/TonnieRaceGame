#include "CEntityTire.h"
#include "Box2DUtils.h" 
#include "CDeltaHelper.h" 
#include "CDrawManager.h" 
#include "CMap.h"
#include <SDL.h>
#include <iostream>
#include "CDebugLogger.h"

CEntityTire::CEntityTire(CEngine* engine, CMap* map, int x, int y) : CEntity(engine), IDrawListener(engine, (int)CDrawManager::Layers::Object), IInputListener(engine), IBox2DListener(engine)
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

	maxForwardSpeed = 500;
	maxBackwardsSpeed = -40;
	maxDriveForce = 400;

	this->engine = engine;
}

void CEntityTire::Draw(SDL_Renderer* renderer)
{
	Box2DUtils::DrawBody(renderer, body, engine->camera, 0, 0, 0, 255, 0, 0, 0, 255, false);
}

void CEntityTire::Input(SDL_Event* event)
{
	switch (event->type)
	{
	case SDL_KEYDOWN:
		switch (event->key.keysym.sym)
		{
		case SDLK_w: controlState |= InputDirections::UP;
			break;
		case SDLK_s: controlState |= InputDirections::DOWN;
			break;
		}
		break;
	case SDL_KEYUP:
		switch (event->key.keysym.sym)
		{
		case SDLK_w: controlState &= ~InputDirections::UP;
			break;
		case SDLK_s: controlState &= ~InputDirections::DOWN;
			break;
		}
		break;
	case SDL_CONTROLLERBUTTONDOWN:
	case SDL_CONTROLLERBUTTONUP:
		OnControllerButton(event->cbutton);
		break;
	}
}

void CEntityTire::OnControllerButton(const SDL_ControllerButtonEvent sdlEvent)
{
	if (sdlEvent.button == SDL_CONTROLLER_BUTTON_RIGHTSHOULDER)
	{
		if (sdlEvent.state == SDL_PRESSED)
		{
			controlState |= InputDirections::UP;
			std::cout << "RIGHT SHOULDER PRESSED \n";
		}
		else if (sdlEvent.state == SDL_RELEASED)
		{
			controlState &= ~InputDirections::UP;
			std::cout << "RIGHT SHOULDER RELEASED\n";
		}
	}
	else if (sdlEvent.button == SDL_CONTROLLER_BUTTON_LEFTSHOULDER)
	{
		if (sdlEvent.state == SDL_PRESSED)
		{
			controlState |= InputDirections::DOWN;
			std::cout << "LEFT SHOULDER PRESSED \n";
		}
		else if (sdlEvent.state == SDL_RELEASED)
		{
			controlState &= ~InputDirections::DOWN;
			std::cout << "LEFT SHOULDER RELEASED\n";
		}
	}
	else if (sdlEvent.button == SDL_CONTROLLER_BUTTON_X)
	{
		if (sdlEvent.state == SDL_PRESSED)
		{
			engine->musicHelper->playTrack("music\\toot.mp3", false);
		}
	}
	else if (sdlEvent.button == SDL_CONTROLLER_BUTTON_START)
	{
		std::cout << "Button: Start\n";
	}
}

void CEntityTire::Update()
{
	UpdateFriction();
	UpdateDrive();
	UpdateTurn();
}

void CEntityTire::Create(b2World* world)
{
}

void CEntityTire::UpdateFriction()
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

void CEntityTire::UpdateDrive()
{
	if (powerupActive && type == 0) {
		maxDriveForce = 500;
	}
	else {
		maxDriveForce = 400;
	}

	float desiredSpeed = 0;
	switch (controlState)
	{
	case InputDirections::UP: desiredSpeed = maxForwardSpeed;
		break;
	case InputDirections::DOWN: desiredSpeed = maxBackwardsSpeed;
		break;
	default: return;
	}

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

void CEntityTire::UpdateTurn()
{
	float desiredTorque = 0;
	switch (controlState)
	{
	case InputDirections::UP: desiredTorque = 15;
		break;
	case InputDirections::DOWN: desiredTorque = -15;
		break;
	default: return;
	}

	body->ApplyTorque(desiredTorque, true);
}

b2Vec2 CEntityTire::GetLateralVelocity()
{
	b2Vec2 currentRightNormal = body->GetWorldVector(b2Vec2(1, 0));
	return b2Dot(currentRightNormal, body->GetLinearVelocity()) * currentRightNormal;
}

b2Vec2 CEntityTire::GetForwardVelocity()
{
	b2Vec2 currentForwardNormal = body->GetWorldVector(b2Vec2(0, 1));
	return b2Dot(currentForwardNormal, body->GetLinearVelocity()) * currentForwardNormal;
}
