#include "CEngine.h"
#include "CDrawManager.h"
#include "CInputManager.h"
#include "CEntityManager.h"
#include "CProfileManager.h"
#include "CCollisionHelper.h"
#include "CBox2DManager.h"
#include "CEntitySmallSquare.h"
#include "CDeltaHelper.h"
#include "CStateManager.h"
#include "CFontManager.h"
#include "CSpriteSheetManager.h"
#include "CTextureManager.h"
#include "CCamera.h"
#include "CDebugLogger.h"
#include "CCameraManager.h"
#include "CLevelFactory.h"
#include <time.h>
#include <iostream>
#include <Box2D\Box2D.h>
#include <SDL.h>
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "CEntityCar.h"
#include "AdHelper.h"
#include "CDebugLogger.h"
#include "CTimerHelper.h"

CEngine::CEngine()
{
	gameControllerConnected = false;
	windowHeight = 720;
	windowWidth = 1280;
	fpsCounter = 1;
	level = 1;
	showFPSCounter = true;
	multiPlayer = false;

	musicHelper = new MusicHelper();
	spriteSheetManager = new CSpriteSheetManager(this);
	collisionHelper = new CCollisionHelper();
	deltaHelper = new CDeltaHelper();
	drawManager = new CDrawManager(this);
	fontManager = new CFontManager(this);
	inputManager = new CInputManager();
	cameraManager = new CCameraManager(this);
	entityManager = new CEntityManager();
	profileManager = new CProfileManager();
	box2DManager = new CBox2DManager(this);
	stateManager = new CStateManager(this);
	textureManager = new CTextureManager(this);
	timerHelper = new CTimerHelper();

	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Tonnie's Grote Racewereld", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	
	SDL_Surface* icon = IMG_Load("Resources/Images/favicon.ico");
	SDL_SetWindowIcon(window, icon);

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
				gameControllerConnected = true;
			}
			else
			{
				fprintf(stderr, "Could not open gamecontroller %i: %s\n", i, SDL_GetError());
			}
		}
	}

	EGameState state = EGameState::Loading;
	stateManager->changeState(state, this);
	musicHelper->playTrack("Resources/Music/title.mp3", false);
	Tick();
}

CEngine::~CEngine()
{
	delete entityManager;
	delete adHelper;
	delete drawManager;
	delete inputManager;
	delete profileManager;
	delete box2DManager;
	delete stateManager;
	delete deltaHelper;
	delete currentMap;
	delete fontManager;
	delete cameraManager;
	delete world;
	delete musicHelper;
	delete collisionHelper;
	delete spriteSheetManager;
	delete textureManager;

	SDL_DestroyRenderer(renderer);
	SDL_Quit();
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
						cameraManager->UpdateViewPort();
					break;
				}
			} else if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_PAGEDOWN:
					deltaHelper->SetScale(deltaHelper->GetScale() - 0.05);
					break;
				case SDLK_PAGEUP:
					deltaHelper->SetScale(deltaHelper->GetScale() + 0.05);
					break;
				case SDLK_HOME:
					deltaHelper->SetScale(1);
					break;
				case SDLK_F1:
					//Alles vrijspelen
					CDebugLogger::PrintDebug("CHEAT: Alles vrijspelen");
					break;
				}
			}
			stateManager->getCurrentState()->input(this, &event);
		}

		stateManager->getCurrentState()->update(this);
		stateManager->getCurrentState()->draw(this);
	}
}

void CEngine::ResizeWindow(int width, int height)
{
	windowHeight = height;
	windowWidth = width;
	SDL_SetWindowSize(window, windowWidth, windowHeight);
}
