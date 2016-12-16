#include "CEntityCarAI.h"
#include "CEntityTireAI.h"
#include "CDebugLogger.h"
#include "CDeltaHelper.h"
#include "CEntitySpawn.h"
#include "CStateManager.h"
#include "Box2DUtils.h"
#include "CDrawManager.h"
#include "CMap.h"
#include <iostream>
#include <string>
#include "CIntegerHelper.h"
#include "CEntityParticleEmitter.h"
#include <SDL_image.h>
#include "CTextureManager.h"

#ifndef DEGTORAD
#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
#endif


CEntityCarAI::CEntityCarAI(CEngine* engine, CMap* map) : CEntity(engine), IDrawListener(engine, (int)CDrawManager::Layers::Object), IBox2DListener(engine)
{
	this->SetType(Type::CAR);
	this->currentCheckpoint = -1;
	this->currentLap = 0;
	this->currentWaypoint = -1;
	this->debugVisible = false;
	this->backupTimer = 0;
	this->backingupTimer = 0;
	this->shouldBackup = false;

	carGenetics = new CarGenetics();
	carGenetics->SetBitString("0000001010000101000010010110000111110100000000101000000000110000001111");

	this->spriteSheet = engine->textureManager->GetTexture("Images/spritesheet_vehicles.png");
	srcRect = {590, 0, 41, 66};

	bodyDef.type = b2_dynamicBody;
	body = engine->world->CreateBody(&bodyDef);
	body->SetUserData(this);

	CEntitySpawn* spawn = map->GetSpawn();
	double xPos = spawn->x;
	double yPos = spawn->y;


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
	b2Fixture* fixture = body->CreateFixture(&polygon, carGenetics->carDensity);
	b2RevoluteJointDef jointDef;
	jointDef.bodyA = body;
	jointDef.enableLimit = true;
	jointDef.lowerAngle = 0;
	jointDef.upperAngle = 0;
	jointDef.localAnchorB.SetZero();

	CEntityTireAI* tire = new CEntityTireAI(engine, map, spawn->x, spawn->y, carGenetics);
	tire->ChangeZIndex(zIndex - 1);
	jointDef.bodyB = tire->body;
	jointDef.localAnchorA.Set(0.5 + xPos, 1.75f + yPos);
	engine->world->CreateJoint(&jointDef);
	tires.push_back(tire);

	tire = new CEntityTireAI(engine, map, spawn->x, spawn->y, carGenetics);
	tire->ChangeZIndex(zIndex - 1);
	jointDef.bodyB = tire->body;
	jointDef.localAnchorA.Set(7.5 + xPos, 1.75f + yPos);
	engine->world->CreateJoint(&jointDef);
	tires.push_back(tire);

	tire = new CEntityTireAI(engine, map, spawn->x, spawn->y, carGenetics);
	tire->ChangeZIndex(zIndex - 1);
	jointDef.bodyB = tire->body;
	jointDef.localAnchorA.Set(0.5 + xPos, 10.5f + yPos);
	flJoint = static_cast<b2RevoluteJoint*>(engine->world->CreateJoint(&jointDef));
	tires.push_back(tire);

	tire = new CEntityTireAI(engine, map, spawn->x, spawn->y, carGenetics);
	tire->ChangeZIndex(zIndex - 1);
	jointDef.bodyB = tire->body;
	jointDef.localAnchorA.Set(7.5 + xPos, 10.5f + yPos);
	frJoint = static_cast<b2RevoluteJoint*>(engine->world->CreateJoint(&jointDef));
	tires.push_back(tire);

	this->finishCallback = nullptr;
	this->engine = engine;
}

CEntityCarAI::~CEntityCarAI()
{
	delete carGenetics;
}

void CEntityCarAI::Draw(SDL_Renderer* renderer)
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
	SDL_Point center = {20.5, 33};

	SDL_Rect dstrect = {((aabb.upperBound.x + aabb.lowerBound.x) / 2 * 5) - engine->camera->GetXPos() - (srcRect.w / 2), ((aabb.upperBound.y + aabb.lowerBound.y) / 2 * 5) - engine->camera->GetYPos() - (srcRect.h / 2), 41, 66};

	SDL_RenderCopyEx(engine->renderer, spriteSheet, &srcRect, &dstrect, angle, &center, SDL_FLIP_VERTICAL);

	if (!debugVisible) { return; }
	Box2DUtils::DrawBody(renderer, body, engine->camera, 0, 0, 0, 0, 0, 0, 255, 255, false);
}

void CEntityCarAI::CollisionBegin(CEntity* collider)
{
	if (collider->GetType() == Type::WAYPOINT)
	{
		CEntityWaypoint* waypoint = static_cast<CEntityWaypoint*>(collider);
		ProcessWaypoint(waypoint);
	}
	else if (collider->GetType() == Type::CHECKPOINT)
	{
		CEntityCheckpoint* checkpoint = static_cast<CEntityCheckpoint*>(collider);
		ProcessCheckpoint(checkpoint);
	}
}

void CEntityCarAI::CollisionEnd(CEntity* collider)
{
}

void CEntityCarAI::ProcessCheckpoint(CEntityCheckpoint* checkpoint)
{
	if (currentCheckpoint + 1 == engine->currentMap->checkpoints && checkpoint->isFinish)
	{
		if (currentLap + 1 == engine->currentMap->laps)
		{
			FinishCallback();
		}
		else
		{
			currentCheckpoint = checkpoint->checkpointIndex;
			currentLap++;
		}
	}
	else
	{
		currentCheckpoint = checkpoint->checkpointIndex;
	}
}

void CEntityCarAI::ProcessWaypoint(CEntityWaypoint* waypoint)
{
	if (waypoint->index == currentWaypoint)
	{
		if (currentWaypoint == engine->currentMap->waypoints.size() - 1)
		{
			ChangeWaypoint(engine->currentMap->waypoints[0]);
			currentWaypoint = 0;
		}
		else
		{
			ChangeWaypoint(engine->currentMap->waypoints[currentWaypoint + 1]);
			currentWaypoint++;
		}
	}
}

void CEntityCarAI::ChangeWaypoint(CEntityWaypoint* waypoint)
{
	heading = waypoint;
	biasX = CIntegerHelper::GetRandomIntBetween(-(waypoint->radius), waypoint->radius);
	biasY = CIntegerHelper::GetRandomIntBetween(-(waypoint->radius), waypoint->radius);
}

void CEntityCarAI::ActivatePowerup(CEntityPowerup* powerup)
{
	activePowerup = powerup;
}

void CEntityCarAI::SetFinishCallback(std::function<void(IBox2DListener*)> callback)
{
	finishCallback = callback;
}

void CEntityCarAI::FinishCallback()
{
	if (finishCallback != nullptr)
	{
		finishCallback(this);
	}
}


void CEntityCarAI::Update()
{
	if (heading == nullptr)
	{
		ChangeWaypoint(engine->currentMap->waypoints[currentWaypoint + 1]);
		currentWaypoint++;
	}

	b2AABB aabb;
	aabb.lowerBound = b2Vec2(FLT_MAX, FLT_MAX);
	aabb.upperBound = b2Vec2(-FLT_MAX, -FLT_MAX);
	b2Fixture* fixture = body->GetFixtureList();
	while (fixture != NULL)
	{
		aabb.Combine(aabb, fixture->GetAABB(0));
		fixture = fixture->GetNext();
	}

	b2Vec2 veca = {(aabb.lowerBound.x + aabb.upperBound.x) / 2, (aabb.lowerBound.y + aabb.upperBound.y) / 2};
	b2Vec2 vecb = heading->body->GetPosition();

	double deltaX = veca.x - (vecb.x + biasX);
	double deltaY = veca.y - (vecb.y + biasY);

	double angle = (atan2(deltaY, deltaX) * 180 / M_PI) + 90.0f;
	if (angle < 270 && angle > 180)
	{
		angle = angle - 360;
	}

	double carAngle = body->GetAngle() * 180 / M_PI;
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
	double turnPerTimeStep = turnSpeedPerSec / (1.0 / engine->deltaHelper->delta);
	double desiredAngle = -headingAngle * DEGTORAD;
	if (desiredAngle < -lockAngle)
	{
		desiredAngle = -lockAngle;
	}
	else if (desiredAngle > lockAngle)
	{
		desiredAngle = lockAngle;
	}

	if (shouldBackup)
	{
		desiredAngle = -desiredAngle;
	}

	double angleNow = flJoint->GetJointAngle();
	double angleToTurn = desiredAngle - angleNow;
	angleToTurn = b2Clamp(angleToTurn, -turnPerTimeStep, turnPerTimeStep);
	double newAngle = angleNow + (angleToTurn);
	flJoint->SetLimits(newAngle, newAngle);
	frJoint->SetLimits(newAngle, newAngle);

	b2Vec2 velocity = body->GetLinearVelocity();
	if ((int)(velocity.Normalize()) < 5)
	{
		backupTimer += engine->deltaHelper->delta;
	}
	else
	{
		backupTimer = 0;
	}

	if (backupTimer > 1.5)
	{
		shouldBackup = true;
	}


	b2Vec2 vecc = veca - vecb;
	float distance = vecc.Normalize();

	if (desiredAngle < 0)
	{
		desiredAngle = -desiredAngle;
	}

	if (shouldBackup && backingupTimer < 1)
	{
		backingupTimer += engine->deltaHelper->delta;
		for (CEntityTireAI* tire : tires)
		{
			tire->maxForwardSpeed = -65;
		}
	}
	else
	{
		shouldBackup = false;
		backingupTimer = 0;
		for (CEntityTireAI* tire : tires)
		{
			if (distance > (velocity.Normalize() * carGenetics->slowDownBias))
			{
				tire->maxForwardSpeed = carGenetics->maxForwardSpeed - (desiredAngle * carGenetics->maxForwardSpeed);
			}
			else
			{
				tire->maxForwardSpeed = 0;
			}
		}
	}
}

void CEntityCarAI::Create(b2World* world)
{
}

void CEntityCarAI::CarGenetics::GetBitString()
{
	std::string geneticString;
	std::string carDensityBinary = std::bitset<10>(carDensity * 100).to_string();
	std::string slowDownBiasBinary = std::bitset<10>(slowDownBias * 100).to_string();
	std::string maxForwardSpeedBinary = std::bitset<10>(maxForwardSpeed).to_string();
	std::string maxDriveForceBinary = std::bitset<10>(maxDriveForce).to_string();
	std::string angularImpulseBiasBinary = std::bitset<10>(angularImpulseBias * 100).to_string();
	std::string dragForceBiasBinary = std::bitset<10>(dragForceBias).to_string();
	std::string desiredTorqueBinary = std::bitset<10>(desiredTorque).to_string();

	geneticString += carDensityBinary + slowDownBiasBinary + maxForwardSpeedBinary + maxDriveForceBinary + angularImpulseBiasBinary + dragForceBiasBinary + desiredTorqueBinary;
}

void CEntityCarAI::CarGenetics::SetBitString(std::string bitString)
{
	std::string carDensityBinary = bitString.substr(0, 10);
	std::string slowDownBiasBinary = bitString.substr(10, 10);
	std::string maxForwardSpeedBinary = bitString.substr(20, 10);
	std::string maxDriveForceBinary = bitString.substr(30, 10);
	std::string angularImpulseBiasBinary = bitString.substr(40, 10);
	std::string dragForceBiasBinary = bitString.substr(50, 10);
	std::string desiredTorqueBinary = bitString.substr(60, 10);

	carDensity = ((float)CIntegerHelper::BitStringToInt(carDensityBinary) / 100);
	slowDownBias = ((float)CIntegerHelper::BitStringToInt(slowDownBiasBinary) / 100);
	maxForwardSpeed = CIntegerHelper::BitStringToInt(maxForwardSpeedBinary);
	maxDriveForce = CIntegerHelper::BitStringToInt(maxDriveForceBinary);
	angularImpulseBias = ((float)CIntegerHelper::BitStringToInt(angularImpulseBiasBinary) / 100);
	dragForceBias = CIntegerHelper::BitStringToInt(dragForceBiasBinary);
	desiredTorque = CIntegerHelper::BitStringToInt(desiredTorqueBinary);
}
