#include "CEntityWaypoint.h"
#include "CEntityCar.h"
#include "CDebugLogger.h"
#include "Box2DUtils.h"
#include "CDrawManager.h"

CEntityWaypoint::CEntityWaypoint(CEngine * engine, double x, double y, int index) : CEntity(engine), IDrawListener(engine, (int)CDrawManager::Layers::Object), IBox2DListener(engine), IInputListener(engine)
{
	visible = false;
	this->SetType(Type::WAYPOINT);
	this->index = index;

	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(x, y);

	b2CircleShape circleShape;
	circleShape.m_p.Set(0, 0);
	radius = 20;
	circleShape.m_radius = radius;

	b2FixtureDef fixtureDef;
	fixtureDef.isSensor = true;
	fixtureDef.shape = &circleShape;

	body = engine->world->CreateBody(&bodyDef);
	body->SetUserData(this);
	b2Fixture* fix = body->CreateFixture(&fixtureDef);

	this->engine = engine;
}

CEntityWaypoint::~CEntityWaypoint()
{
}

void CEntityWaypoint::Draw(SDL_Renderer * renderer)
{
	if (!visible) { return; }
	Box2DUtils::DrawBody(renderer, body, engine->camera, 0, 0, 0, 0, 0, 0, 255, 255, false);
}

void CEntityWaypoint::Update()
{
}

void CEntityWaypoint::Create(b2World * world)
{
}

void CEntityWaypoint::CollisionBegin(CEntity* collider)
{
	if (collider->GetType() == Type::CAR) {
		CEntityCar* car = static_cast<CEntityCar*>(collider);
	}
}

void CEntityWaypoint::CollisionEnd(CEntity * collider)
{
}

void CEntityWaypoint::Input(SDL_Event* event)
{
	switch (event->type)
	{
	case SDL_KEYDOWN:
		switch (event->key.keysym.sym)
		{
		case SDLK_g:
			visible = !visible;
			break;
		}
	}
}
