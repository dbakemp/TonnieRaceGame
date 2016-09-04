#include "SDL.h"
#include "CEntityCircle.h"

CEntityCircle::CEntityCircle(CEngine *engine): IDrawListener(engine)
{
}

void CEntityCircle::Draw(SDL_Renderer *renderer)
{
	SDL_Rect rect = {25, 25, 50, 50};
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderFillRect(renderer, &rect);
}
