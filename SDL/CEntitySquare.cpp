#include "SDL.h"
#include "CEntitySquare.h"
#include "CEntity.h"
#include "CEngine.h"
#include "CCamera.h"
#include "IBox2DListener.h"
#include "Box2DUtils.h"
#include <math.h>
#include <cstdlib>

CEntitySquare::CEntitySquare(CEngine *engine): CEntity(engine), IDrawListener(engine), IInputListener(engine), IBox2DListener(engine)
{
	xPos = -100;
	yPos = -100;
	height = 30;
	width = 30;

	rCol = 255;
	gCol = 25;
	bCol = 25;

	xVel = 0;
	yVel = 0;
	friction = 0.5;


	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(xPos, yPos);
	bodyDef.angle = 0;
	bodyDef.fixedRotation = true;
	body = engine->world->CreateBody(&bodyDef);
	polygon.SetAsBox(width, height);
	fixture.shape = &polygon;
	fixture.density = 1;
	body->CreateFixture(&fixture);

	this->engine = engine;
}

void CEntitySquare::Draw(SDL_Renderer *renderer)
{
	/*b2Vec2 position = body->GetPosition(); 
	SDL_Rect rect = { position.x - engine->camera->posX, position.y - engine->camera->posY, (width * 30) * 2, (width * 30) * 2 };
	SDL_SetRenderDrawColor(renderer, rCol, gCol, bCol, 255);
	SDL_RenderFillRect(renderer, &rect);*/
	Box2DUtils::DrawBody(renderer, body, engine->camera, rCol, gCol, bCol, 255, rCol, gCol, bCol, 255, false);
}

void CEntitySquare::Input(SDL_Event *event) {
	switch (event->type) {
		case SDL_KEYDOWN:
			if(event->key.keysym.sym == SDLK_w) {
				yAcc = -1;
			} else if (event->key.keysym.sym == SDLK_s) {
				yAcc = 1;
			}
			if (event->key.keysym.sym == SDLK_a) {
				xAcc = -1;
			} else if (event->key.keysym.sym == SDLK_d) {
				xAcc = 1;
			}
		break;
		case SDL_KEYUP:
			if (event->key.keysym.sym == SDLK_w) {
				yAcc = 0;
			}
			if (event->key.keysym.sym == SDLK_s) {
				yAcc = 0;
			}
			if (event->key.keysym.sym == SDLK_a) {
				xAcc = 0;
			}
			if (event->key.keysym.sym == SDLK_d) {
				xAcc = 0;
			}
		break;
	}
}

void CEntitySquare::Update()
{
	xPos = body->GetPosition().x;
	yPos = body->GetPosition().y;

	if (yAcc == -1) {
		body->ApplyForce(b2Vec2(0, -150), body->GetWorldCenter(), true);
	}
	if (yAcc == 1) {
		body->ApplyForce(b2Vec2(0, 150), body->GetWorldCenter(), true);
	}
	if (xAcc == -1) {
		body->ApplyForce(b2Vec2(-150, 0), body->GetWorldCenter(), true);
	}
	if (xAcc == 1) {
		body->ApplyForce(b2Vec2(150, 0), body->GetWorldCenter(), true);
	}
}

void CEntitySquare::Create(b2World * world)
{
}
