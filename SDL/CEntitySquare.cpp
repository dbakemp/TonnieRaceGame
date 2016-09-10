#include "SDL.h"
#include "CEntitySquare.h"
#include "CEntity.h"
#include "CEngine.h"
#include "CCamera.h"
#include <math.h>
#include <cstdlib>

CEntitySquare::CEntitySquare(CEngine *engine): CEntity(engine), IDrawListener(engine), IInputListener(engine)
{
	xPos = 6000;
	yPos = 6000;
	height = 100;
	width = 60;

	rCol = 255;
	gCol = 25;
	bCol = 25;

	xVel = 0;
	yVel = 0;
	friction = 0.5;
	this->engine = engine;
}

void CEntitySquare::Draw(SDL_Renderer *renderer)
{
	SDL_Rect rect = { xPos-engine->camera->posX, yPos-engine->camera->posY, width,  height };
	SDL_SetRenderDrawColor(renderer, rCol, gCol, bCol, 255);
	SDL_RenderFillRect(renderer, &rect);
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
	xVel += xAcc;
	yVel += yAcc;

	float speed = sqrt(xVel*xVel + yVel*yVel);

	if (speed > friction) {
		speed -= friction;
	}
	else {
		speed = 0;
	}

	float angle = atan2(yVel, xVel);
	xVel = cos(angle) * speed;
	yVel = sin(angle) * speed;

	xPos += xVel;
	yPos += yVel;
}
