#include "CEntityCar.h"
#include "CEntityTire.h"
#include "Box2DUtils.h"

#ifndef DEGTORAD
#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
#endif

CEntityCar::CEntityCar(CEngine * engine) : CEntity(engine), IDrawListener(engine), IInputListener(engine), IBox2DListener(engine)
{
	bodyDef.type = b2_dynamicBody;
	body = engine->world->CreateBody(&bodyDef);
	body->SetAngularDamping(5);

	b2Vec2 vertices[8];
	vertices[0].Set(1.5, 0);
	vertices[1].Set(3, 2.5);
	vertices[2].Set(2.8, 5.5);
	vertices[3].Set(1, 10);
	vertices[4].Set(-1, 10);
	vertices[5].Set(-2.8, 5.5);
	vertices[6].Set(-3, 2.5);
	vertices[7].Set(-1.5, 0);
	b2PolygonShape polygonShape;
	polygonShape.Set(vertices, 8);
	b2Fixture* fixture = body->CreateFixture(&polygonShape, 0.5f);
	b2RevoluteJointDef jointDef;
	jointDef.bodyA = body;
	jointDef.enableLimit = true;
	jointDef.lowerAngle = 0;
	jointDef.upperAngle = 0;
	jointDef.localAnchorB.SetZero();

	CEntityTire* tire = new CEntityTire(engine);
	jointDef.bodyB = tire->body;
	jointDef.localAnchorA.Set(-3, 0.75f);
	engine->world->CreateJoint(&jointDef);
	tires.push_back(tire);

	tire = new CEntityTire(engine);
	jointDef.bodyB = tire->body;
	jointDef.localAnchorA.Set(3, 0.75f);
	engine->world->CreateJoint(&jointDef);
	tires.push_back(tire);

	tire = new CEntityTire(engine);
	jointDef.bodyB = tire->body;
	jointDef.localAnchorA.Set(-3, 8.5f);
	flJoint = (b2RevoluteJoint*)engine->world->CreateJoint(&jointDef);
	tires.push_back(tire);

	tire = new CEntityTire(engine);
	jointDef.bodyB = tire->body;
	jointDef.localAnchorA.Set(3, 8.5f);
	frJoint = (b2RevoluteJoint*)engine->world->CreateJoint(&jointDef);
	tires.push_back(tire);

	this->engine = engine;
}

void CEntityCar::Draw(SDL_Renderer * renderer)
{
	Box2DUtils::DrawBody(renderer, body, engine->camera, 0, 0, 255, 255, 0, 0, 255, 255, false);
}

void CEntityCar::Input(SDL_Event * event)
{
	switch (event->type) {
	case SDL_KEYDOWN:
		switch (event->key.keysym.sym) {
		case SDLK_a: controlState |= InputDirections::LEFT; break;
		case SDLK_d: controlState |= InputDirections::RIGHT; break;
		}
		break;
	case SDL_KEYUP:
		switch (event->key.keysym.sym) {
		case SDLK_a: controlState &= ~InputDirections::LEFT; break;
		case SDLK_d: controlState &= ~InputDirections::RIGHT; break;
		}
		break;
	}
}

void CEntityCar::Update()
{
	//control steering
	float lockAngle = 45 * DEGTORAD;
	float turnSpeedPerSec = 160 * DEGTORAD;//from lock to lock in 0.5 sec
	float turnPerTimeStep = turnSpeedPerSec / 60.0f;
	float desiredAngle = 0;

	switch (controlState) {
		case InputDirections::RIGHT: desiredAngle = lockAngle; break;
		case InputDirections::LEFT: desiredAngle = -lockAngle; break;
	}

	float angleNow = flJoint->GetJointAngle();
	float angleToTurn = desiredAngle - angleNow;
	angleToTurn = b2Clamp(angleToTurn, -turnPerTimeStep, turnPerTimeStep);
	float newAngle = angleNow + angleToTurn;
	flJoint->SetLimits(newAngle, newAngle);
	frJoint->SetLimits(newAngle, newAngle);
}

void CEntityCar::Create(b2World * world)
{
}