#include "SDL.h"
#include "CEntitySmallSquare.h"
#include "CEntity.h"
#include "CEngine.h"
#include "CCamera.h"
#include "IBox2DListener.h"
#include <cstdlib>

CEntitySmallSquare::CEntitySmallSquare(CEngine *engine): CEntity(engine), IDrawListener(engine), IBox2DListener(engine)
{
	xPos = rand() % 1000;
	yPos = rand() % 1000;
	height = 10;
	width = 10;

	rCol = 25;
	gCol = 255;
	bCol = 25;

	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(xPos, yPos);
	bodyDef.angle = 0;
	body = engine->world->CreateBody(&bodyDef);
	polygon.SetAsBox(width, height);
	fixture.shape = &polygon;
	fixture.density = 10;
	body->CreateFixture(&fixture);

	this->engine = engine;
}

void CEntitySmallSquare::Draw(SDL_Renderer *renderer)
{
	b2Vec2 position = body->GetPosition();
	SDL_Rect rect = { position.x - engine->camera->posX, position.y - engine->camera->posY, width, height };
	SDL_SetRenderDrawColor(renderer, rCol, gCol, bCol, 255);
	SDL_RenderFillRect(renderer, &rect);
}

void CEntitySmallSquare::Update()
{
}

void CEntitySmallSquare::Create(b2World * world)
{
}