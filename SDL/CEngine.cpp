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
	musicHelper = new MusicHelper();

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
			inputManager->Tick(&event);
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

	/* SDL CONTROLLER SUPPORT */
	//void AddController(int id)
	//{
	//	if (SDL_IsGameController(id)) {
	//		SDL_GameController *pad = SDL_GameControllerOpen(id);

	//		if (pad) {
	//			SDL_Joystick *joy = SDL_GameControllerGetJoystick(pad);
	//			int instanceID = SDL_JoystickInstanceID(joy);

	//			// You can add to your own map of joystick IDs to controllers here.
	//			YOUR_FUNCTION_THAT_CREATES_A_MAPPING(id, pad);
	//		}
	//	}
	//}

	//void RemoveController(int id)
	//{
	//	SDL_GameController *pad = YOUR_FUNCTION_THAT_RETRIEVES_A_MAPPING(id);
	//	SDL_GameControllerClose(pad);
	//}

	//void OnControllerButton(const SDL_ControllerButtonEvent sdlEvent)
	//{
	//	// Button presses and axis movements both sent here as SDL_ControllerButtonEvent structures
	//}

	//void OnControllerAxis(const SDL_ControllerAxisEvent sdlEvent)
	//{
	//	// Axis movements and button presses both sent here as SDL_ControllerAxisEvent structures
	//}

	//void EventLoop()
	//{
	//	SDL_Event sdlEvent;

	//	while (SDL_PollEvent(&sdlEvent)) {
	//		switch (sdlEvent.type) {

	//		case SDL_CONTROLLERDEVICEADDED:
	//			AddController(sdlEvent.cdevice);
	//			break;

	//		case SDL_CONTROLLERDEVICEREMOVED:
	//			RemoveController(sdlEvent.cdevice);
	//			break;

	//		case SDL_CONTROLLERBUTTONDOWN:
	//		case SDL_CONTROLLERBUTTONUP:
	//			OnControllerButton(sdlEvent.cbutton);
	//			break;

	//		case SDL_CONTROLLERAXISMOTION:
	//			OnControllerAxis(sdlEvent.caxis);
	//			break;

	//			// YOUR OTHER EVENT HANDLING HERE

	//		}
	//	}
	//}
}
