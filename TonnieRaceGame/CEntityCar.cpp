#include "CEntityCar.h"
#include "CEntityTire.h"
#include "CDebugLogger.h"
#include "CDeltaHelper.h"
#include "CEntitySpawn.h"
#include "CStateManager.h"
#include "Box2DUtils.h"
#include "CDrawManager.h"
#include "CMap.h"
#include <iostream>
#include <string>
#include <SDL_image.h>
#include "CEntityPowerup.h"
#include "CTextureManager.h"
#include "CCameraManager.h"
#include "CCameraManager.h"

#ifndef DEGTORAD
#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
#endif

CEntityCar::CEntityCar(CEngine* engine, CMap* map) : CEntity(engine), IDrawListener(engine, (int)CDrawManager::Layers::Object), IInputListener(engine), IBox2DListener(engine)
{
	this->SetType(Type::CAR);
	this->currentCheckpoint = -1;
	this->currentLap = 0;
	this->debugVisible = false;
	this->powerupActive = false;
	this->activePowerup = nullptr;
	this->powerupTimer = 0;

	SDL_Surface* texture = IMG_Load("Resources/Images/spritesheet_vehicles.png");
	this->spriteSheet = engine->textureManager->GetTexture("Images/spritesheet_vehicles.png");
	srcRect = {631, 0, 41, 66};

	bodyDef.type = b2_dynamicBody;
	body = engine->world->CreateBody(&bodyDef);
	body->SetUserData(this);

	CEntitySpawn* spawn = map->GetSpawn();
	double xPos = spawn->x;
	double yPos = spawn->y;

	emitter = new CEntityParticleEmitter(engine);
	emitter->SetPosition(xPos * 5, yPos * 5);

	b2Vec2 vertices[8];

	vertices[0].Set(0 + xPos, 2 + yPos);
	vertices[1].Set(2 + xPos, 0 + yPos);
	vertices[2].Set(6 + xPos, 0 + yPos);
	vertices[3].Set(8 + xPos, 2 + yPos);
	vertices[4].Set(8 + xPos, 11 + yPos);
	vertices[5].Set(6 + xPos, 13 + yPos);
	vertices[6].Set(2 + xPos, 13 + yPos);
	vertices[7].Set(0 + xPos, 11 + yPos);

	polygon.Set(vertices, 8);
	b2Fixture* fixture = body->CreateFixture(&polygon, 0.1f);
	b2RevoluteJointDef jointDef;
	jointDef.bodyA = body;
	jointDef.enableLimit = true;
	jointDef.lowerAngle = 0;
	jointDef.upperAngle = 0;
	jointDef.localAnchorB.SetZero();

	CEntityTire* tire = new CEntityTire(engine, map, spawn->x, spawn->y);
	tire->ChangeZIndex(zIndex - 1);
	jointDef.bodyB = tire->body;
	jointDef.localAnchorA.Set(0.5 + xPos, 1.75f + yPos);
	engine->world->CreateJoint(&jointDef);
	tires.push_back(tire);

	tire = new CEntityTire(engine, map, spawn->x, spawn->y);
	tire->ChangeZIndex(zIndex - 1);
	jointDef.bodyB = tire->body;
	jointDef.localAnchorA.Set(7.5 + xPos, 1.75f + yPos);
	engine->world->CreateJoint(&jointDef);
	tires.push_back(tire);

	tire = new CEntityTire(engine, map, spawn->x, spawn->y);
	tire->ChangeZIndex(zIndex - 1);
	jointDef.bodyB = tire->body;
	jointDef.localAnchorA.Set(0.5 + xPos, 10.5f + yPos);
	flJoint = static_cast<b2RevoluteJoint*>(engine->world->CreateJoint(&jointDef));
	tires.push_back(tire);

	tire = new CEntityTire(engine, map, spawn->x, spawn->y);
	tire->ChangeZIndex(zIndex - 1);
	jointDef.bodyB = tire->body;
	jointDef.localAnchorA.Set(7.5 + xPos, 10.5f + yPos);
	frJoint = static_cast<b2RevoluteJoint*>(engine->world->CreateJoint(&jointDef));
	tires.push_back(tire);

	this->finishCallback = nullptr;
	this->engine = engine;
}

CEntityCar::~CEntityCar()
{
}

void CEntityCar::Draw(SDL_Renderer* renderer)
{
	aabb.lowerBound = b2Vec2(FLT_MAX, FLT_MAX);
	aabb.upperBound = b2Vec2(-FLT_MAX, -FLT_MAX);
	b2Fixture* fixture = body->GetFixtureList();
	while (fixture != NULL)
	{
		aabb.Combine(aabb, fixture->GetAABB(0));
		fixture = fixture->GetNext();
	}

	double angle = body->GetAngle() * (180.0 / M_PI);
	SDL_Point center = {20.5, 33};

	SDL_Rect dstrect = {((aabb.upperBound.x + aabb.lowerBound.x) / 2 * 5) - engine->cameraManager->GetCurrentCamera()->GetXPos() - (srcRect.w / 2), ((aabb.upperBound.y + aabb.lowerBound.y) / 2 * 5) - engine->cameraManager->GetCurrentCamera()->GetYPos() - (srcRect.h / 2), 41, 66};

	SDL_RenderCopyEx(renderer, spriteSheet, &srcRect, &dstrect, angle, &center, SDL_FLIP_VERTICAL);

	if (!debugVisible) { return; }
	Box2DUtils::DrawBody(renderer, body, engine->cameraManager->GetCurrentCamera(), 0, 0, 0, 0, 0, 0, 255, 255, false);
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
			debugVisible = !debugVisible;
			break;
		case SDLK_SPACE:
			if (activePowerup != nullptr && !powerupActive)
			{
				powerupActive = true;
				for (CEntityTire* tire : tires)
				{
					tire->powerupActive = true;
					tire->type = static_cast<int>(activePowerup->type);
				}
				CDebugLogger::PrintDebug("Powerup geactiveerd");
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

void CEntityCar::CollisionBegin(CEntity* collider)
{
	if (collider->GetType() == Type::CHECKPOINT)
	{
		CEntityCheckpoint* checkpoint = static_cast<CEntityCheckpoint*>(collider);
		ProcessCheckpoint(checkpoint);
	}
}

void CEntityCar::CollisionEnd(CEntity* collider)
{
}

void CEntityCar::ProcessCheckpoint(CEntityCheckpoint* checkpoint)
{
	if (checkpoint->checkpointIndex == currentCheckpoint + 1)
	{
		currentCheckpoint = checkpoint->checkpointIndex;
	}
	else if (currentCheckpoint + 1 == engine->currentMap->checkpoints && checkpoint->isFinish)
	{
		if (currentLap + 1 == engine->currentMap->laps)
		{
			CDebugLogger::PrintDebug("Race finish here");
			FinishCallback();
		}
		else
		{
			currentCheckpoint = checkpoint->checkpointIndex;
			currentLap++;
		}
	}
}

void CEntityCar::ActivatePowerup(CEntityPowerup* powerup)
{
	this->activePowerup = powerup;
	CDebugLogger::PrintDebug("Powerup opgepakt");
}

void CEntityCar::SetFinishCallback(std::function<void(IBox2DListener*)> callback)
{
	finishCallback = callback;
}

void CEntityCar::FinishCallback()
{
	if (finishCallback != nullptr)
	{
		finishCallback(this);
	}
}


void CEntityCar::Update()
{
	//control steering
	double lockAngle = 50 * DEGTORAD;
	double turnSpeedPerSec = 250 * DEGTORAD;
	double turnPerTimeStep = turnSpeedPerSec / (1.0 / engine->deltaHelper->GetScaledDelta());
	double desiredAngle = 0;

	switch (controlState)
	{
	case InputDirections::RIGHT: desiredAngle = lockAngle;
		break;
	case InputDirections::LEFT: desiredAngle = -lockAngle;
		break;
	}

	if (powerupActive && activePowerup != nullptr && static_cast<int>(this->activePowerup->type) == 1)
	{
		desiredAngle = 0 - desiredAngle;
	}

	double angleNow = flJoint->GetJointAngle();
	double angleToTurn = desiredAngle - angleNow;
	angleToTurn = b2Clamp(angleToTurn, -turnPerTimeStep, turnPerTimeStep);
	double newAngle = angleNow + (angleToTurn);
	flJoint->SetLimits(newAngle, newAngle);
	frJoint->SetLimits(newAngle, newAngle);

	if (powerupActive)
	{
		powerupTimer += engine->deltaHelper->GetScaledDelta();
		if (powerupTimer > (rand() % (10 - 5 + 1) + 5))
		{
			CDebugLogger::PrintDebug("Powerup verlopen");
			powerupTimer = 0;
			powerupActive = false;
			activePowerup = nullptr;
			for (CEntityTire* tire : tires)
			{
				tire->powerupActive = false;
			}
		}
	}
	emitter->SetPosition(((aabb.upperBound.x + aabb.lowerBound.x) / 2 * 5), ((aabb.upperBound.y + aabb.lowerBound.y) / 2 * 5));
}

void CEntityCar::Create(b2World* world)
{
}
