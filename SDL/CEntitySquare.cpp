#include "SDL.h"
#include "CEntitySquare.h"
#include "CEntity.h"

CEntitySquare::CEntitySquare(CEngine *engine): CEntity(engine), IDrawListener(engine), IInputListener(engine)
{
	xPos = 0;
	yPos = 0;
	xVel = 0;
	yVel = 0;
}

void CEntitySquare::Draw(SDL_Renderer *renderer)
{
	SDL_Rect rect = { xPos, yPos, 100, 100 };
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	SDL_RenderFillRect(renderer, &rect);
}

void CEntitySquare::Input(SDL_Event *event) {
	switch (event->type) {
		case SDL_KEYDOWN:
			switch (event->key.keysym.sym) {
				case SDLK_LEFT:
					xVel = -2;
					break;
				case SDLK_RIGHT:
					xVel = 2;
					break;
				case SDLK_UP:
					yVel = -2;
					break;
				case SDLK_DOWN:
					yVel = 2;
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
