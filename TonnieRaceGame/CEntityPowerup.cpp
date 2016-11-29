#include "CEntityTire.h"
#include "Box2DUtils.h" 
#include "CDeltaHelper.h" 
#include "CDrawManager.h" 
#include "CMap.h"
#include <SDL.h>
#include <iostream>
#include "SDL_image.h"
#include "stdlib.h"
#include "CEntityCar.h"

CEntityPowerup::CEntityPowerup(CEngine * engine, CMap * map, double xPos, double yPos) : CEntity(engine), IDrawListener(engine, (int)CDrawManager::Layers::Object), IBox2DListener(engine), IInputListener(engine)
{
	this->SetType(Type::POWERUP);
	this->visible = true;
	this->devVisible = false;
	this->xPos = xPos;
	this->yPos = yPos;

	int count = 2;
	int rowNumber = 0;
	int columnNumber = rand() % 2;
	int size = 36;

	this->textureX = columnNumber * size;
	this->textureY = rowNumber * size;
	this->spriteSheet = map->spriteSheetPowerUps;
	this->textureHeight = size;
	this->textureWidth = size;

	srcRect = { this->textureX, this->textureY, this->textureWidth, this->textureHeight };

	// Box2D 
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(xPos / 5, yPos / 5);

	b2CircleShape circleShape;
	circleShape.m_p.Set(3.5,3.5);
	circleShape.m_radius = 3.5;

	b2FixtureDef fixtureDef;
	fixtureDef.isSensor = true;
	fixtureDef.shape = &circleShape;

	body = engine->world->CreateBody(&bodyDef);
	body->SetUserData(this);
	b2Fixture* fix = body->CreateFixture(&fixtureDef);

	this->engine = engine;
}

void CEntityPowerup::Draw(SDL_Renderer * renderer)
{
	if (devVisible) 
	{
		Box2DUtils::DrawBody(renderer, body, engine->camera, 0, 0, 0, 0, 0, 0, 255, 255, false);
	}
	if (visible && yPos > engine->camera->posY - this->textureHeight && xPos > engine->camera->posX - this->textureWidth && yPos < engine->camera->posY + engine->windowHeight && xPos < engine->camera->posX + engine->windowWidth)
	{
		SDL_Rect dstrect = { -engine->camera->posX + (xPos), -engine->camera->posY + (yPos), this->textureWidth, this->textureHeight };
		SDL_RenderCopy(engine->renderer, spriteSheet, &srcRect, &dstrect);
	}
}

void CEntityPowerup::Update()
{
}

void CEntityPowerup::CollisionBegin(CEntity * collider)
{
	if (visible) 
	{
		visible = false;
		std::cout << "Je hebt een powerup opgepakt!\n";
	}
	if (collider->GetType() == Type::CAR) {
		CEntityCar* car = static_cast<CEntityCar*>(collider);

	}
}

void CEntityPowerup::CollisionEnd(CEntity * collider)
{
}

void CEntityPowerup::Input(SDL_Event * event)
{
	switch (event->type)
	{
	case SDL_KEYDOWN:
		switch (event->key.keysym.sym)
		{
		case SDLK_f:
			devVisible = !devVisible;
			break;
		}
	}
}

void CEntityPowerup::Create(b2World * world)
{
}