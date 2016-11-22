#include "CEngine.h"
#include "CDrawManager.h"
#include "CInputManager.h"
#include "CEntityManager.h"
#include "CBox2DManager.h"
#include "CEntitySmallSquare.h"
#include "CStateManager.h"
#include "CCamera.h"
#include "CLevelFactory.h"
#include <time.h>
#include <iostream>
#include <Box2D\Box2D.h>
#include <SDL.h>
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "CEntityCar.h"

CEngine::CEngine() {
	int windowHeight = 720;
	int windowWidth = 1280;
	fps = 1;

	musicHelper = new MusicHelper();
	drawManager = new CDrawManager();
	inputManager = new CInputManager();
	entityManager = new CEntityManager();
	box2DManager = new CBox2DManager();
	stateManager = new CStateManager();

	CLevelFactory* factory = new CLevelFactory(this);
	factory->LoadMap("Resources/Maps/map1.json");
	srand(time(NULL));
	
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("RaceGame", 100, 100, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	EGameState state = Start;
	stateManager->changeState(state, this);

	Tick();
}

void CEngine::Tick()
{
	running = true;

	double nextFrame = static_cast<double>(SDL_GetTicks());

	while (running)
	{
		stateManager->getCurrentState()->update(this);

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
