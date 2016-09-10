#include "SDL.h"
#include "CEntityCircle.h"
#include "CEntity.h"
#include "CEngine.h"
#include "CCamera.h"
#include <cstdlib>

CEntityCircle::CEntityCircle(CEngine *engine): CEntity(engine), IDrawListener(engine)
{
	xPos = rand() % 1200;
	yPos = rand() % 1200;
	height = rand() % 100;
	width = rand() % 100;

	rCol = rand() % 255;
	gCol = rand() % 255;
	bCol = rand() % 255;

	xVel = 0;
	yVel = 0;
	this->engine = engine;
}

void CEntityCircle::Draw(SDL_Renderer *renderer)
{
	SDL_Rect rect = { xPos - engine->camera->posX, yPos - engine->camera->posY, height, width };
	SDL_SetRenderDrawColor(renderer, rCol, gCol, bCol, 255);
	SDL_RenderFillRect(renderer, &rect);
}

void CEntityCircle::Update()
{
}
