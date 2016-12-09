#define _CRT_SECURE_NO_WARNINGS
#include "SDL.h"
#include "CStateManager.h"
#include "SDL_image.h"
#include "CPlayState.h"
#include "CEngine.h"
#include "CEntityCarAI.h"
#include "CEntityCar.h"
#include "CEntitySmallSquare.h"
#include "CEntityBuild.h"
#include "CInputManager.h"
#include "CEntityManager.h"
#include "CAdManager.h"
#include "CDeltaHelper.h"
#include "CDrawManager.h"
#include "CLevelFactory.h"
#include "CBox2DManager.h"
#include "CCollisionHelper.h"
#include "CEntityLapCounter.h"
#include "CEntityFpsCounter.h"
#include "CEntitySpeedoMeter.h"
#include "SDL_ttf.h"
#include "CDebugLogger.h"

void CPlayState::init(CEngine* engine)
{
	this->engine = engine;

	SDL_Renderer* renderer;
	renderer = SDL_CreateRenderer(engine->window, -1, 0);
	SDL_RenderClear(renderer);

	b2Vec2 gravity(0, 0);

	engine->world = new b2World(gravity);

	engine->world->SetContactListener(engine->collisionHelper);

	SDL_QueryTexture(backmapTexture, NULL, NULL, &texW, &texH);

	engine->adManager = new CAdManager(engine);

	CLevelFactory* factory = new CLevelFactory(engine);

	if (engine->level == 1)
	{
		CDebugLogger::PrintDebug("Loading LVL 1");
		factory->LoadMap("Resources/Maps/map1.json");
		engine->musicHelper->playTrack("Resources/Music/beep.mp3", true);
	}
	else if (engine->level == 2)
	{
		CDebugLogger::PrintDebug("Loading LVL 2");
		factory->LoadMap("Resources/Maps/map2.json");
		engine->musicHelper->playTrack("Resources/Music/boerharms.mp3", true);
	}
	else
	{
		CDebugLogger::PrintDebug("Error loading level");
	}

	engine->currentMap = factory->map;

	camera = new CCamera(engine);

	engine->camera = camera;

	CEntityCar* car = new CEntityCar(engine, factory->map);
	int spawns = factory->map->availableSpawns.size();
	for (int i = 0; i < spawns; i++) {
		new CEntityCarAI(engine, factory->map);
	}

	camera->SetChild(car);

	CEntityFpsCounter* fpsCounter = new CEntityFpsCounter(engine);
	CEntityLapCounter* lapCounter = new CEntityLapCounter(engine);
	CEntitySpeedoMeter* speedoMeter = new CEntitySpeedoMeter(engine);
	speedoMeter->ChangeZIndex(speedoMeter->zIndex+1);
	CEntityBuild* build = new CEntityBuild(engine);

	speedoMeter->SetChild(car);
	lapCounter->SetLapCountable(car);

}

void CPlayState::clean(CEngine* engine)
{
	engine->drawManager->Clear();
	engine->inputManager->Clear();
	engine->box2DManager->Clear();
	engine->entityManager->Clear();

	delete camera;
	camera = nullptr;
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
	camera->Update();
	engine->entityManager->Tick();
	engine->world->Step(engine->deltaHelper->delta, 8, 3);
	checkSeque();
}

void CPlayState::draw(CEngine* engine)
{
	SDL_SetRenderDrawColor(engine->renderer, 0, 0, 0, 255);
	SDL_RenderClear(engine->renderer);
	engine->drawManager->Tick(engine->renderer);
}

void CPlayState::input(CEngine* engine, SDL_Event * event)
{
	if (event->type == SDL_KEYDOWN) {

		switch (event->key.keysym.sym)
		{
		case SDLK_ESCAPE:
			stateSeque = EGameState::Menu;
			shouldSeque = true;
			break;
		}
	}

	engine->inputManager->Tick(event);
}

void CPlayState::checkSeque()
{
	if (!shouldSeque) { return; }

	engine->stateManager->changeState(stateSeque, engine);
}

CPlayState::CPlayState(CEngine* engine)
{
	init(engine);
}
