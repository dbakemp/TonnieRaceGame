#include "SDL.h"
#include "CEngine.h"
#include "CDrawManager.h"
#include "CInputManager.h"
#include "CEntityCircle.h"
#include "CEntitySquare.h"

CEngine::CEngine() {
	drawManager = new CDrawManager();
	inputManager = new CInputManager();

	CEntitySquare *sq1 = new CEntitySquare(this);
	CEntityCircle *cl1 = new CEntityCircle(this);

	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("test", 100, 100, 1920, 1080, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	int running = 1;

	while (running)
	{
		Tick();
	}
}

void CEngine::Tick()
{
	SDL_Event *event = new SDL_Event();
	while (SDL_PollEvent(event) != 0)
	{
		inputManager->Tick(event);
	}

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	SDL_RenderClear(renderer);

	drawManager->Tick(renderer);

	SDL_RenderPresent(renderer);
}
