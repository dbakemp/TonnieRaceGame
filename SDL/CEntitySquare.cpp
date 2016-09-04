#include "SDL.h"
#include "CEntitySquare.h"

CEntitySquare::CEntitySquare(CEngine *engine): IDrawListener(engine), IInputListener(engine)
{
	xPos = 0;
	yPos = 0;
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
					xPos += -2;
					break;
				case SDLK_RIGHT:
					xPos += 2;
					break;
				case SDLK_UP:
					yPos += -2;
					break;
				case SDLK_DOWN:
					yPos += 2;
					break;
				default:
					break;
			}
			break;
	}
}