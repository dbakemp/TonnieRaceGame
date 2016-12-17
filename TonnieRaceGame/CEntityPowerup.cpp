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
#include "CEntityCarAI.h"
#include "CDebugLogger.h"
#include "CCameraManager.h"

CEntityPowerup::CEntityPowerup(CEngine* engine, CMap* map, double xPos, double yPos) : CEntity(engine), IDrawListener(engine, (int)CDrawManager::Layers::Object), IBox2DListener(engine), IInputListener(engine)
{
	this->SetType(Type::POWERUP);
	this->visible = true;
	this->devVisible = false;
	this->xPos = xPos;
	this->yPos = yPos;
	this->timer = 0;

	int count = 2;
	PowerupType type = static_cast<PowerupType>(rand() % 2);
	int rowNumber = 0;
	int columnNumber = static_cast<int>(type);
	int size = 36;

	this->textureX = columnNumber * size;
	this->textureY = rowNumber * size;
	this->spriteSheet = map->spriteSheetPowerUps;
	this->textureHeight = size;
	this->textureWidth = size;
	this->type = type;

	srcRect = {this->textureX, this->textureY, this->textureWidth, this->textureHeight};

	// Box2D 
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(xPos / 5, yPos / 5);

	b2CircleShape circleShape;
	circleShape.m_p.Set(3.5, 3.5);
	circleShape.m_radius = 3.5;

	b2FixtureDef fixtureDef;
	fixtureDef.isSensor = true;
	fixtureDef.shape = &circleShape;

	body = engine->world->CreateBody(&bodyDef);
	body->SetUserData(this);
	b2Fixture* fix = body->CreateFixture(&fixtureDef);

	this->engine = engine;
}

CEntityPowerup::~CEntityPowerup()
{
}

void CEntityPowerup::Draw(SDL_Renderer* renderer)
{
	if (!visible)
	{
		timer += engine->deltaHelper->GetScaledDelta();
		if (timer > 5)
		{
			visible = true;
			timer = 0;
		}
	}
	if (devVisible)
	{
		Box2DUtils::DrawBody(renderer, body, engine->cameraManager->GetCurrentCamera(), 0, 0, 0, 0, 0, 0, 255, 255, false);
	}
	if (visible && yPos > engine->cameraManager->GetCurrentCamera()->GetYPos() - this->textureHeight && xPos > engine->cameraManager->GetCurrentCamera()->GetXPos() - this->textureWidth && yPos < engine->cameraManager->GetCurrentCamera()->GetYPos() + engine->windowHeight && xPos < engine->cameraManager->GetCurrentCamera()->GetXPos() + engine->windowWidth)
	{
		SDL_Rect dstrect = {-engine->cameraManager->GetCurrentCamera()->GetXPos() + (xPos), -engine->cameraManager->GetCurrentCamera()->GetYPos() + (yPos), this->textureWidth, this->textureHeight};
		SDL_RenderCopy(renderer, spriteSheet, &srcRect, &dstrect);
	}
}

void CEntityPowerup::Update()
{
}

void CEntityPowerup::CollisionBegin(CEntity* collider)
{
	if (visible)
	{
		visible = false;
		if (collider->GetType() == Type::CAR)
		{
			CEntityCar* car = dynamic_cast<CEntityCar*>(collider);
			if (car != NULL)
			{
				car->ActivatePowerup(this);
			}
		}
	}
}

void CEntityPowerup::CollisionEnd(CEntity* collider)
{
}

void CEntityPowerup::Input(SDL_Event* event)
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

void CEntityPowerup::Create(b2World* world)
{
}
