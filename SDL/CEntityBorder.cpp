#include "CEntityBorder.h"
#include "Box2DUtils.h"

CEntityBorder::CEntityBorder(CEngine * engine) : CEntity(engine), IDrawListener(engine), IBox2DListener(engine)
{
	bodyDef.type = b2_staticBody;
	body = engine->world->CreateBody(&bodyDef);

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

	this->engine = engine;
}

CEntityBorder::CEntityBorder(CEngine* engine, p2t::Triangle* triangle) : CEntity(engine), IDrawListener(engine), IBox2DListener(engine) {
	bodyDef.type = b2_staticBody;
	body = engine->world->CreateBody(&bodyDef);

	b2Vec2 vertices[3];
	vertices[0].Set(triangle->GetPoint(0)->x, triangle->GetPoint(0)->y);
	vertices[1].Set(triangle->GetPoint(1)->x, triangle->GetPoint(1)->y);
	vertices[2].Set(triangle->GetPoint(2)->x, triangle->GetPoint(2)->y);

	b2PolygonShape polygonShape;
	polygonShape.Set(vertices, 3);
	b2Fixture* fixture = body->CreateFixture(&polygonShape, 0.5f);

	this->engine = engine;
}

void CEntityBorder::Draw(SDL_Renderer * renderer)
{
	Box2DUtils::DrawBody(renderer, body, engine->camera, 0, 255, 0, 255, 0, 0, 240, 0, false);
}

void CEntityBorder::Update()
{
}

void CEntityBorder::Create(b2World * world)
{
}
