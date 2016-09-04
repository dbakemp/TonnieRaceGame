#include "SDL.h"
#include "CEntitySquare.h"

CEntitySquare::CEntitySquare(CEngine *engine): IDrawListener(engine)
{
}

void CEntitySquare::Draw(SDL_Renderer *renderer)
{
	SDL_Rect rect = { 0, 0, 100, 100 };
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	SDL_RenderFillRect(renderer, &rect);

}
