#include "CEntityCheckpoint.h"
#include "CEntityCar.h"
#include "CDebugLogger.h"
#include "Box2DUtils.h"

CEntityCheckpoint::CEntityCheckpoint(CEngine* engine, b2Vec2* start, b2Vec2* end, int index) : CEntity(engine), IDrawListener(engine), IBox2DListener(engine)
{
	this->SetType(Type::CHECKPOINT);
	this->checkpointIndex = index;

	bodyDef.type = b2_staticBody;
	b2Vec2 vertices[8];

	vertices[0].Set(start->x, start->y);
	vertices[1].Set(end->x, end->y);
	vertices[2].Set(end->x+1, end->y + 1);
	vertices[3].Set(start->x-1, start->y - 1);

	polygon.Set(vertices, 4);
	b2FixtureDef fixtureDef;
	fixtureDef.isSensor = true;
	fixtureDef.shape = &polygon;

	body = engine->world->CreateBody(&bodyDef);
	body->SetUserData(this);
	b2Fixture* fix = body->CreateFixture(&fixtureDef);

	this->engine = engine;
}

void CEntityCheckpoint::Draw(SDL_Renderer * renderer)
{
	//Box2DUtils::DrawBody(renderer, body, engine->camera, 0, 0, 0, 0, 0, 0, 255, 255, false);
}

void CEntityCheckpoint::Update()
{
}

void CEntityCheckpoint::Create(b2World * world)
{
}

void CEntityCheckpoint::CollisionBegin(CEntity* collider)
{
	if (collider->GetType() == Type::CAR) {
		CEntityCar* car = static_cast<CEntityCar*>(collider);
	}
}

void CEntityCheckpoint::CollisionEnd(CEntity* collider)
{
}