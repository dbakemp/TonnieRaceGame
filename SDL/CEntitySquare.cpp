#include "SDL.h"
#include "CEntitySquare.h"
#include "CEntity.h"
#include "CEngine.h"
#include "CCamera.h"
#include <cstdlib>

CEntitySquare::CEntitySquare(CEngine *engine): CEntity(engine), IDrawListener(engine), IInputListener(engine)
{
	xPos = rand() % 800;
	yPos = rand() % 600;
	height = rand() % 100;
	width = rand() % 100;

	rCol = rand() % 255;
	gCol = rand() % 255;
	bCol = rand() % 255;

	xVel = 0;
	yVel = 0;
	this->engine = engine;
}

void CEntitySquare::Draw(SDL_Renderer *renderer)
{
	SDL_Rect rect = { xPos-engine->camera->posX, yPos-engine->camera->posY, height, width };
	SDL_SetRenderDrawColor(renderer, rCol, gCol, bCol, 255);
	SDL_RenderFillRect(renderer, &rect);
}

void CEntitySquare::Input(SDL_Event *event) {
	switch (event->type) {
		case SDL_KEYDOWN:
			switch (event->key.keysym.sym) {
				case SDLK_LEFT:
					xVel = -3;
					break;
				case SDLK_RIGHT:
					xVel = 3;
					break;
				case SDLK_UP:
					yVel = -3;
					break;
				case SDLK_DOWN:
					yVel = 3;
					break;
				default:
					break;
			}
			break;
		case SDL_KEYUP:
			switch (event->key.keysym.sym) {
			case SDLK_LEFT:
				xVel = 0;
				break;
			case SDLK_RIGHT:
				xVel = 0;
				break;
			case SDLK_UP:
				yVel = 0;
				break;
			case SDLK_DOWN:
				yVel = 0;
				break;
			default:
				break;
			}
			break;
	}
}

void CEntitySquare::Update()
{
	xPos += xVel;
	yPos += yVel;
}
