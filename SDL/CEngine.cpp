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

	int running = 1;

	while (running)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event) != 0)
		{
		}

		Tick();
	}

	SDL_Delay(4000);
}

void CEngine::Tick()
{
	SDL_Renderer *renderer = NULL;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	SDL_RenderClear(renderer);

	inputManager->Tick();
	drawManager->Tick(renderer);

	SDL_RenderPresent(renderer);
}
