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
#include <SDL_image.h>

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

	SDL_Surface* texture = IMG_Load("Resources/Images/spritesheet_vehicles.png");
	this->spriteSheet = SDL_CreateTextureFromSurface(engine->renderer, texture);
	srcRect = { 590, 0, 41, 66 };

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
	b2Fixture* fixture = body->CreateFixture(&polygon, 0.1f);
	b2RevoluteJointDef jointDef;
	jointDef.bodyA = body;
	jointDef.enableLimit = true;
	jointDef.lowerAngle = 0;
	jointDef.upperAngle = 0;
	jointDef.localAnchorB.SetZero();

	CEntityTireAI* tire = new CEntityTireAI(engine, map, spawn->x, spawn->y);
	tire->ChangeZIndex(zIndex - 1);
	jointDef.bodyB = tire->body;
	jointDef.localAnchorA.Set(0.5 + xPos, 1.75f + yPos);
	engine->world->CreateJoint(&jointDef);
	tires.push_back(tire);

	tire = new CEntityTireAI(engine, map, spawn->x, spawn->y);
	tire->ChangeZIndex(zIndex - 1);
	jointDef.bodyB = tire->body;
	jointDef.localAnchorA.Set(7.5 + xPos, 1.75f + yPos);
	engine->world->CreateJoint(&jointDef);
	tires.push_back(tire);

	tire = new CEntityTireAI(engine, map, spawn->x, spawn->y);
	tire->ChangeZIndex(zIndex - 1);
	jointDef.bodyB = tire->body;
	jointDef.localAnchorA.Set(0.5 + xPos, 10.5f + yPos);
	flJoint = static_cast<b2RevoluteJoint*>(engine->world->CreateJoint(&jointDef));
	tires.push_back(tire);

	tire = new CEntityTireAI(engine, map, spawn->x, spawn->y);
	tire->ChangeZIndex(zIndex - 1);
	jointDef.bodyB = tire->body;
	jointDef.localAnchorA.Set(7.5 + xPos, 10.5f + yPos);
	frJoint = static_cast<b2RevoluteJoint*>(engine->world->CreateJoint(&jointDef));
	tires.push_back(tire);

	this->engine = engine;
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
	SDL_Point center = { 20.5, 33 };

	SDL_Rect dstrect = { ((aabb.upperBound.x + aabb.lowerBound.x) / 2 * 5) - engine->camera->posX - (srcRect.w / 2), ((aabb.upperBound.y + aabb.lowerBound.y) / 2 * 5) - engine->camera->posY - (srcRect.h / 2), 41, 66 };

	SDL_RenderCopyEx(engine->renderer, spriteSheet, &srcRect, &dstrect, angle, &center, SDL_FLIP_VERTICAL);

	if (!debugVisible) { return; }
	Box2DUtils::DrawBody(renderer, body, engine->camera, 0, 0, 0, 0, 0, 0, 255, 255, false);
}

void CEntityCarAI::CollisionBegin(CEntity* collider)
{
	if (collider->GetType() == Type::WAYPOINT) {
		CEntityWaypoint* waypoint = static_cast<CEntityWaypoint*>(collider);
		ProcessWaypoint(waypoint);
	}
}

void CEntityCarAI::CollisionEnd(CEntity* collider)
{
}

void CEntityCarAI::ProcessCheckpoint(CEntityCheckpoint * checkpoint)
{
	if (currentCheckpoint + 1 == engine->currentMap->checkpoints && checkpoint->isFinish) {
		if (currentLap + 1 == engine->currentMap->laps) {
			CDebugLogger::PrintDebug("Race finish here");
			engine->stateManager->changeState(Win, engine);
		}
		else {
			currentCheckpoint = checkpoint->checkpointIndex;
			currentLap++;
		}
	}
	else {
		currentCheckpoint = checkpoint->checkpointIndex;
	}
}

void CEntityCarAI::ProcessWaypoint(CEntityWaypoint * waypoint)
{
	if (waypoint->index == currentWaypoint) {
		if (currentWaypoint == engine->currentMap->waypoints.size()-1) {
			ChangeWaypoint(engine->currentMap->waypoints[0]);
			currentWaypoint = 0;
		}
		else {
			ChangeWaypoint(engine->currentMap->waypoints[currentWaypoint + 1]);
			currentWaypoint++;
		}
		CDebugLogger::PrintDebug("New Waypoint");
	}
}

void CEntityCarAI::ChangeWaypoint(CEntityWaypoint * waypoint)
{
	heading = waypoint;
	biasX = CIntegerHelper::GetRandomIntBetween(-(waypoint->radius), waypoint->radius);
	biasY = CIntegerHelper::GetRandomIntBetween(-(waypoint->radius), waypoint->radius);
}


void CEntityCarAI::Update()
{
	if (heading == nullptr) {
		ChangeWaypoint(engine->currentMap->waypoints[currentWaypoint+1]);
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

	b2Vec2 veca = { (aabb.lowerBound.x+aabb.upperBound.x)/2, (aabb.lowerBound.y + aabb.upperBound.y) / 2 };
	b2Vec2 vecb = heading->body->GetPosition();

	double deltaX = veca.x - (vecb.x+biasX);
	double deltaY = veca.y - (vecb.y+biasY);

	double angle = (atan2(deltaY, deltaX) * 180 / M_PI) +90.0f;
	if (angle < 270 && angle > 180) {
		angle = angle - 360;
	}
	
	double carAngle = body->GetAngle() * 180 / M_PI;
	while (carAngle <= -180) {
		carAngle += 360;
	}
	while (carAngle > 180) {
		carAngle -= 360;
	}

	double headingAngle;
	headingAngle = carAngle - angle;
	if (headingAngle < -180) {
		headingAngle += 360;
	} else if (headingAngle > 180) {
		headingAngle -= 360;
	}

	//control steering
	double lockAngle = 50 * DEGTORAD;
	double turnSpeedPerSec = 250 * DEGTORAD;
	double turnPerTimeStep = turnSpeedPerSec / (1.0 / engine->deltaHelper->delta);
	double desiredAngle = -headingAngle * DEGTORAD;
	if (desiredAngle < -lockAngle) {
		desiredAngle = -lockAngle;
	}
	else if(desiredAngle > lockAngle) {
		desiredAngle = lockAngle;
	}

	double angleNow = flJoint->GetJointAngle();
	double angleToTurn = desiredAngle - angleNow;
	angleToTurn = b2Clamp(angleToTurn, -turnPerTimeStep, turnPerTimeStep);
	double newAngle = angleNow + (angleToTurn);
	flJoint->SetLimits(newAngle, newAngle);
	frJoint->SetLimits(newAngle, newAngle);
}

void CEntityCarAI::Create(b2World* world)
{
}
