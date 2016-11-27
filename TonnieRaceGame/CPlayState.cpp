#define _CRT_SECURE_NO_WARNINGS
#include "SDL.h"
#include "CStateManager.h"
#include "SDL_image.h"
#include "CPlayState.h"
#include "CEngine.h"
#include "CEntityCar.h"
#include "CEntitySmallSquare.h"
#include "CEntityBuild.h"
#include "CInputManager.h"
#include "CEntityManager.h"
#include "CDrawManager.h"
#include "CLevelFactory.h"
#include "CCollisionHelper.h"
#include "CEntityLapCounter.h"
#include "CEntityFpsCounter.h"
#include "SDL_ttf.h"


void CPlayState::init()
{
	return;
}

void CPlayState::init(CEngine* engine)
{
	TTF_Init();
	TTF_Font* fpsFont = TTF_OpenFont("Resources/Fonts/opensans.ttf", 16);

	b2Vec2 gravity(0, 0);

	engine->world = new b2World(gravity);

	engine->world->SetContactListener(engine->collisionHelper);

	SDL_QueryTexture(backmapTexture, NULL, NULL, &texW, &texH);

	CLevelFactory* factory = new CLevelFactory(engine);
	factory->LoadMap("Resources/Maps/map1.json");

	camera = new CCamera();
	camera->windowHeight = 720;
	camera->windowWidth = 1280;

	engine->camera = camera;

	CEntityCar* car = new CEntityCar(engine, factory->map);
	camera->SetChild(car);

	CEntityFpsCounter* fpsCounter = new CEntityFpsCounter(engine, fpsFont);
	CEntityBuild* build = new CEntityBuild(engine, fpsFont);
	CEntityLapCounter* lapCounter = new CEntityLapCounter(engine, fpsFont);
	lapCounter->SetLapCountable(car);

	engine->musicHelper->playTrack("music\\boerharms.mp3", true);
}

void CPlayState::clean()
{
}

void CPlayState::pause()
{
}

void CPlayState::resume()
{
}

void CPlayState::handleEvents(CEngine* engine)
{
}

void CPlayState::update(CEngine* engine)
{
	SDL_Event event;

	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
		{
			engine->running = false;
			SDL_Quit();
		}
		else
		{
			engine->inputManager->Tick(&event);
		}
	}

	SDL_SetRenderDrawColor(engine->renderer, 0, 0, 0, 255);
	SDL_RenderClear(engine->renderer);

	engine->entityManager->Tick();
	engine->world->Step(0.016f, 8, 3);
	camera->Update();

	engine->drawManager->Tick(engine->renderer);
}

void CPlayState::draw(CEngine* engine)
{
}

CPlayState::CPlayState(CEngine* engine)
{
	init(engine);
}

CPlayState::~CPlayState()
{
	clean();
}
