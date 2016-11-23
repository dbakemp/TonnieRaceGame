#include "CEntityCar.h"
#include "CEntityTire.h"
#include "Box2DUtils.h"
#include "CMap.h"
#include <iostream>
#include <SDL_image.h>

#ifndef DEGTORAD
#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
#endif

CEntityCar::CEntityCar(CEngine* engine, CMap* map) : CEntity(engine), IDrawListener(engine), IInputListener(engine), IBox2DListener(engine)
{
	SDL_Surface* texture = IMG_Load("Resources/Images/spritesheet_vehicles.png");
	this->spriteSheet = SDL_CreateTextureFromSurface(engine->renderer, texture);
	srcRect = { 631, 0, 41, 66 };

	bodyDef.type = b2_dynamicBody;
	body = engine->world->CreateBody(&bodyDef);
	//body->SetAngularDamping(5);

	double xPos = map->spawnX;
	double yPos = map->spawnY;

	b2Vec2 vertices[8];
	/*vertices[0].Set(1.5 + xPos, 0 + yPos);
	vertices[1].Set(3 + xPos, 2.5 + yPos);
	vertices[2].Set(2.8 + xPos, 5.5 + yPos);
	vertices[3].Set(1 + xPos, 10 + yPos);
	vertices[4].Set(-1 + xPos, 10 + yPos);
	vertices[5].Set(-2.8 + xPos, 5.5 + yPos);
	vertices[6].Set(-3 + xPos, 2.5 + yPos);
	vertices[7].Set(-1.5 + xPos, 0 + yPos);*/

	vertices[0].Set(0 + xPos, 0 + yPos);
	vertices[1].Set(8 + xPos, 0 + yPos);
	vertices[2].Set(8 + xPos, 13 + yPos);
	vertices[3].Set(0 + xPos, 13 + yPos);

	b2PolygonShape polygonShape;
	polygonShape.Set(vertices, 4);
	b2Fixture* fixture = body->CreateFixture(&polygonShape, 0.1f);
	b2RevoluteJointDef jointDef;
	jointDef.bodyA = body;
	jointDef.enableLimit = true;
	jointDef.lowerAngle = 0;
	jointDef.upperAngle = 0;
	jointDef.localAnchorB.SetZero();

	CEntityTire* tire = new CEntityTire(engine, map);
	jointDef.bodyB = tire->body;
	jointDef.localAnchorA.Set(0.5 + xPos, 1.75f + yPos);
	engine->world->CreateJoint(&jointDef);
	tires.push_back(tire);

	tire = new CEntityTire(engine, map);
	jointDef.bodyB = tire->body;
	jointDef.localAnchorA.Set(7.5 + xPos, 1.75f + yPos);
	engine->world->CreateJoint(&jointDef);
	tires.push_back(tire);

	tire = new CEntityTire(engine, map);
	jointDef.bodyB = tire->body;
	jointDef.localAnchorA.Set(0.5 + xPos, 10.5f + yPos);
	flJoint = static_cast<b2RevoluteJoint*>(engine->world->CreateJoint(&jointDef));
	tires.push_back(tire);

	tire = new CEntityTire(engine, map);
	jointDef.bodyB = tire->body;
	jointDef.localAnchorA.Set(7.5 + xPos, 10.5f + yPos);
	frJoint = static_cast<b2RevoluteJoint*>(engine->world->CreateJoint(&jointDef));
	tires.push_back(tire);

	this->engine = engine;
}

void CEntityCar::Draw(SDL_Renderer* renderer)
{
	b2AABB aabb;
	aabb.lowerBound = b2Vec2(FLT_MAX, FLT_MAX);
	aabb.upperBound = b2Vec2(-FLT_MAX, -FLT_MAX);
	b2Fixture* fixture = body->GetFixtureList();
	while (fixture != NULL)
	{
		aabb.Combine(aabb, fixture->GetAABB(0));
		fixture = fixture->GetNext();
	}

	double angle = body->GetAngle() * (180.0 / M_PI);
	SDL_Point center = { 20.5, 33 };

	SDL_Rect dstrect = { ((aabb.upperBound.x + aabb.lowerBound.x)/2 * 5)-engine->camera->posX-(srcRect.w/2), ((aabb.upperBound.y + aabb.lowerBound.y) / 2 * 5) - engine->camera->posY - (srcRect.h / 2), 41, 66 };

	//SDL_RenderCopy(engine->renderer, spriteSheet, &srcRect, &dstrect);
	SDL_RenderCopyEx(engine->renderer, spriteSheet, &srcRect, &dstrect, angle, &center, SDL_FLIP_VERTICAL);
	//Box2DUtils::DrawBody(renderer, body, engine->camera, 0, 0, 0, 0, 0, 0, 255, 255, false);
}

void CEntityCar::Input(SDL_Event* event)
{
	switch (event->type)
	{
	case SDL_KEYDOWN:
		switch (event->key.keysym.sym)
		{
		case SDLK_a: controlState |= InputDirections::LEFT;
			break;
		case SDLK_d: controlState |= InputDirections::RIGHT;
			break;
		case SDLK_f: 
			if (engine->showFPSCounter)
			{
				engine->showFPSCounter = false;
			}
			else
			{
				engine->showFPSCounter = true;
			}
			break;
		}
		break;
	case SDL_KEYUP:
		switch (event->key.keysym.sym)
		{
		case SDLK_a: controlState &= ~InputDirections::LEFT;
			break;
		case SDLK_d: controlState &= ~InputDirections::RIGHT;
			break;
		}
		break;
	case SDL_CONTROLLERAXISMOTION:
		OnControllerAxis(event->caxis);
		break;
		break;
	}
}


void CEntityCar::OnControllerAxis(const SDL_ControllerAxisEvent sdlEvent)
{
	const int JOYSTICK_DEAD_ZONE = 8000;

	//X axis motion
	if (sdlEvent.axis == 0)
	{
		//Left of dead zone
		if (sdlEvent.value < -JOYSTICK_DEAD_ZONE)
		{
			controlState |= InputDirections::LEFT;
		}
		//Right of dead zone
		else if (sdlEvent.value > JOYSTICK_DEAD_ZONE)
		{
			controlState |= InputDirections::RIGHT;
		}
		else
		{
			controlState &= ~InputDirections::LEFT;
			controlState &= ~InputDirections::RIGHT;
		}
	}
}


void CEntityCar::Update()
{
	//control steering
	float lockAngle = 60 * DEGTORAD;
	float turnSpeedPerSec = 160 * DEGTORAD;//from lock to lock in 0.5 sec
	float turnPerTimeStep = turnSpeedPerSec / 60.0f;
	float desiredAngle = 0;

	switch (controlState)
	{
	case InputDirections::RIGHT: desiredAngle = lockAngle;
		break;
	case InputDirections::LEFT: desiredAngle = -lockAngle;
		break;
	}

	float angleNow = flJoint->GetJointAngle();
	float angleToTurn = desiredAngle - angleNow;
	angleToTurn = b2Clamp(angleToTurn, -turnPerTimeStep, turnPerTimeStep);
	float newAngle = angleNow + angleToTurn;
	flJoint->SetLimits(newAngle, newAngle);
	frJoint->SetLimits(newAngle, newAngle);
}

void CEntityCar::Create(b2World* world)
{
}
