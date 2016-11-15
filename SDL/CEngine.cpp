#include "CEngine.h"
#include "CDrawManager.h"
#include "CInputManager.h"
#include "CEntityManager.h"
#include "CBox2DManager.h"
#include "CEntitySmallSquare.h"
#include "CEntitySquare.h"
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

	b2Vec2 gravity(0, 0);

	world = new b2World(gravity);

	drawManager = new CDrawManager();
	inputManager = new CInputManager();
	entityManager = new CEntityManager();
	box2DManager = new CBox2DManager();
	camera = new CCamera();
	camera->windowHeight = windowHeight;
	camera->windowWidth = windowWidth;

	srand(time(NULL));

	CEntityCar* car = new CEntityCar(this);
	camera->SetChild(car);

	for (int i = 0; i < 200; i++) {
		new CEntitySmallSquare(this);
	}
	
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("RaceGame", 100, 100, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
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
