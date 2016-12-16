#include "CEntityBorder.h"
#include "Box2DUtils.h"
#include "CDrawManager.h"

CEntityBorder::CEntityBorder(CEngine* engine, p2t::Triangle* triangle) : CEntity(engine), IDrawListener(engine, (int)CDrawManager::Layers::Object), IBox2DListener(engine), IInputListener(engine)
{
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

CEntityBorder::~CEntityBorder()
{
}

void CEntityBorder::Draw(SDL_Renderer* renderer)
{
	if (!visible) { return; }
	Box2DUtils::DrawBody(renderer, body, engine->camera, 0, 0, 0, 0, 0, 0, 255, 255, false);
}

void CEntityBorder::Update()
{
}

void CEntityBorder::Create(b2World* world)
{
}

void CEntityBorder::Input(SDL_Event* event)
{
	switch (event->type)
	{
	case SDL_KEYDOWN:
		switch (event->key.keysym.sym)
		{
		case SDLK_f:
			visible = !visible;
			break;
		}
	}
}
