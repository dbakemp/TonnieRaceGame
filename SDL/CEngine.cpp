#include "CEngine.h"
#include "CDrawManager.h"
#include "CInputManager.h"
#include "CEntityManager.h"
#include "CBox2DManager.h"
#include "CEntitySmallSquare.h"
#include "CEntitySquare.h"
#include "CStateManager.h"
#include "CCamera.h"
#include <time.h>
#include <iostream>
#include <Box2D\Box2D.h>
#include <SDL.h>
#include "CEntityCar.h"

CEngine::CEngine() {
	int windowHeight = 720;
	int windowWidth = 1280;
	fps = 1;

	drawManager = new CDrawManager();
	inputManager = new CInputManager();
	entityManager = new CEntityManager();
	box2DManager = new CBox2DManager();
	stateManager = new CStateManager();

	srand(time(NULL));
	
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("RaceGame", 100, 100, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	EGameState state = Playing;
	stateManager->changeState(state, this);

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
			if (event.type == SDL_QUIT) {
				running = false;
				SDL_Quit();
			}
			else {
				inputManager->Tick(&event);
			}
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		entityManager->Tick();
		world->Step(0.016f, 8, 3);
		camera->Update();
		drawManager->Tick(renderer);

		SDL_RenderPresent(renderer);

		int delay = static_cast<Uint32> (nextFrame - static_cast<double>(SDL_GetTicks()));
		if (delay > 0) {
			SDL_Delay(delay);
		}
		nextFrame += 1000.0 / 60;
	}
}
