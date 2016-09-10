#include "SDL.h"
#include "CEngine.h"
#include "CDrawManager.h"
#include "CInputManager.h"
#include "CEntityManager.h"
#include "CEntityCircle.h"
#include "CEntitySquare.h"
#include "CCamera.h"
#include <time.h>
#include <iostream>

CEngine::CEngine() {
	drawManager = new CDrawManager();
	inputManager = new CInputManager();
	entityManager = new CEntityManager();
	camera = new CCamera();

	srand(time(NULL));

	for (int i = 0; i < 10000; i++) {
		new CEntityCircle(this);
	}
	
	CEntity *player = new CEntitySquare(this);
	camera->SetChild(player);

	
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("test", 100, 100, 800, 600, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	Tick();
}

void CEngine::Tick()
{
	int running = 1;

	double nextFrame = static_cast<double>(SDL_GetTicks());

	while (running)
	{
		SDL_Event event;

		while (SDL_PollEvent(&event) != 0)
		{
			inputManager->Tick(&event);
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		camera->Update();
		entityManager->Tick();
		drawManager->Tick(renderer);

		SDL_RenderPresent(renderer);

		int delay = static_cast<Uint32> (nextFrame - static_cast<double>(SDL_GetTicks()));
		if (delay > 0) {
			SDL_Delay(delay);
		}
		nextFrame += 1000.0 / 60;
	}
}
