#define _CRT_SECURE_NO_WARNINGS
#include "SDL.h"
#include "CStateManager.h"
#include "CPlayState.h"
#include "CEngine.h"
#include "CEntityCarAI.h"
#include "CEntityCar.h"
#include "CEntityBuild.h"
#include "CInputManager.h"
#include "CEntityManager.h"
#include "CAdManager.h"
#include "CDeltaHelper.h"
#include "CDrawManager.h"
#include "CLevelFactory.h"
#include "CEntityLapCounter.h"
#include "CEntityFpsCounter.h"
#include "CEntitySpeedoMeter.h"
#include "CCollisionHelper.h"
#include <functional>

void CPlayState::init(CEngine* engine)
{
	this->engine = engine;

	SDL_Renderer* renderer;
	renderer = SDL_CreateRenderer(engine->window, -1, 0);
	SDL_RenderClear(renderer);

	b2Vec2 gravity(0, 0);

	engine->world = new b2World(gravity);

	engine->world->SetContactListener(engine->collisionHelper);

	engine->adManager = new CAdManager(engine);

	CLevelFactory* factory = new CLevelFactory(engine);

	factory->LoadMap("Resources/Maps/" + engine->level);
	engine->musicHelper->playTrack("Resources/Music/beep.mp3", true);

	engine->currentMap = factory->map;

	engine->camera = new CCamera(engine);

	CEntityCar* car = new CEntityCar(engine, factory->map);
	int spawns = factory->map->availableSpawns.size();
	for (int i = 0; i < spawns; i++)
	{
		new CEntityCarAI(engine, factory->map);
	}

	car->SetFinishCallback(std::bind(&CPlayState::OnFinish, this, std::placeholders::_1));
	engine->camera->SetChild(car);

	CEntityFpsCounter* fpsCounter = new CEntityFpsCounter(engine);
	CEntityLapCounter* lapCounter = new CEntityLapCounter(engine);
	CEntitySpeedoMeter* speedoMeter = new CEntitySpeedoMeter(engine);
	speedoMeter->ChangeZIndex(speedoMeter->zIndex + 1);
	CEntityBuild* build = new CEntityBuild(engine);

	speedoMeter->SetChild(car);
	lapCounter->SetLapCountable(car);

	delete factory;
}

void CPlayState::clean(CEngine* engine)
{
	engine->entityManager->Clear();

	int count = engine->world->GetBodyCount();
	b2Body* body = engine->world->GetBodyList();
	for (int i = 0; i < count; i++)
	{
		b2Body* nextBody = body->GetNext();
		engine->world->DestroyBody(body);
		body = nullptr;
		body = nextBody;
	}

	delete engine->adManager;
	engine->adManager = nullptr;
	delete engine->camera;
	engine->camera = nullptr;
	delete engine->world;
	engine->world = nullptr;
	delete engine->currentMap;
	engine->currentMap = nullptr;
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
	engine->camera->Update();
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

void CPlayState::input(CEngine* engine, SDL_Event* event)
{
	if (event->type == SDL_KEYDOWN)
	{
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
	engine->musicHelper->stopAll();
}

void CPlayState::OnFinish(IBox2DListener* car)
{
}

CPlayState::CPlayState(CEngine* engine)
{
	init(engine);
}

CPlayState::~CPlayState()
{
}
