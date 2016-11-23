#include "CEngine.h"
#include "CDrawManager.h"
#include "CInputManager.h"
#include "CEntityManager.h"
#include "CBox2DManager.h"
#include "CEntitySmallSquare.h"
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

CEngine::CEngine()
{
	windowHeight = 720;
	windowWidth = 1280;
	fpsCounter = 1;
	showFPSCounter = true;

	musicHelper = new MusicHelper();
	drawManager = new CDrawManager();
	inputManager = new CInputManager();
	entityManager = new CEntityManager();
	box2DManager = new CBox2DManager();
	stateManager = new CStateManager();

	srand(time(NULL));

	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("RaceGame", 100, 100, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
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

	double nextFrame = static_cast<double>(SDL_GetTicks());
	clock_t current_ticks, delta_ticks;
	clock_t fps = 0;

	while (running)
	{
		current_ticks = clock();
		stateManager->getCurrentState()->update(this);

		SDL_RenderPresent(renderer);

		int delay = static_cast<Uint32>(nextFrame - static_cast<double>(SDL_GetTicks()));
		if (delay > 0)
		{
			SDL_Delay(delay);
		}
		nextFrame += 1000.0 / 60;

		delta_ticks = clock() - current_ticks; //the time, in ms, that took to render the scene
		if (delta_ticks > 0)
			fps = CLOCKS_PER_SEC / delta_ticks;

		this->fpsCounter = fps;
	
	}

	
}
