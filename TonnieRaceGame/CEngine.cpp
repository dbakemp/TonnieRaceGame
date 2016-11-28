#include "CEngine.h"
#include "CDrawManager.h"
#include "CInputManager.h"
#include "CEntityManager.h"
#include "CCollisionHelper.h"
#include "CBox2DManager.h"
#include "CEntitySmallSquare.h"
#include "CDeltaHelper.h"
#include "CStateManager.h"
#include "CCamera.h"
#include "CDebugLogger.h"
#include "CLevelFactory.h"
#include <time.h>
#include <iostream>
#include <Box2D\Box2D.h>
#include <SDL.h>
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "CEntityCar.h"
#include "AdHelper.h"

CEngine::CEngine()
{
	windowHeight = 720;
	windowWidth = 1280;
	fpsCounter = 1;
	showFPSCounter = true;

	//AdHelper* adHelper = new AdHelper();
	musicHelper = new MusicHelper();
	collisionHelper = new CCollisionHelper();
	drawManager = new CDrawManager();
	inputManager = new CInputManager();
	entityManager = new CEntityManager();
	box2DManager = new CBox2DManager();
	stateManager = new CStateManager();
	deltaHelper = new CDeltaHelper();

	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("RaceGame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	SDL_GameController* controller = NULL;
	
	for (int i = 0; i < SDL_NumJoysticks(); ++i)
	{
		if (SDL_IsGameController(i))
		{
			printf("Index \'%i\' is a compatible controller, named \'%s\'\n", i, SDL_GameControllerNameForIndex(i));
			controller = SDL_GameControllerOpen(i);
			if (controller)
			{
				cout << "Sucesfully opened GameController.\n";
				SDL_GameControllerAddMappingsFromFile("Recources\\gamecontrollerdb.txt");
				cout << "Controller mapping DB succesfully loaded.\n";
			}
			else
			{
				fprintf(stderr, "Could not open gamecontroller %i: %s\n", i, SDL_GetError());
			}
		}
	}

	EGameState state = Start;
	stateManager->changeState(state, this);
	musicHelper->playTrack("music\\title.mp3", false);
	Tick();
}

void CEngine::Tick()
{
	running = true;

	while (running)
	{
		deltaHelper->SetDelta();

		SDL_Event event;
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
			{
				running = false;
				SDL_Quit();
			}
			else if (event.type == SDL_WINDOWEVENT) {
				switch (event.window.event) {
					case SDL_WINDOWEVENT_RESIZED:
						ResizeWindow(event.window.data1, event.window.data2);
					break;
				}
			}
			else {
				stateManager->getCurrentState()->input(this, &event);
			}
		}

		stateManager->getCurrentState()->update(this);

		SDL_RenderPresent(renderer);
	}
}

void CEngine::ResizeWindow(int width, int height)
{
	windowHeight = height;
	windowWidth = width;
	SDL_SetWindowSize(window, windowWidth, windowHeight);
}
