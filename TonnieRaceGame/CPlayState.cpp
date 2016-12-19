#define _CRT_SECURE_NO_WARNINGS
#include "SDL.h"
#include "CStateManager.h"
#include "CPlayState.h"
#include "CEngine.h"
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
#include "CCameraManager.h"
#include "CPlayer2ControlSchemeCar.h"
#include "CPlayer1ControlSchemeCar.h"
#include "CAIControlSchemeCar.h"
#include "CEntityPositionCounter.h"

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

	CEntityCar* car = new CEntityCar(engine, factory->map);
	car->SetControlScheme(new CPlayer1ControlSchemeCar(engine));

	car->SetFinishCallback(std::bind(&CPlayState::OnFinish, this, std::placeholders::_1));

	CEntityFpsCounter* fpsCounter = new CEntityFpsCounter(engine);
	CEntityBuild* build = new CEntityBuild(engine);

	engine->cameraManager->AddCamera();
	if (engine->multiPlayer)
	{
		engine->cameraManager->AddCamera();
	}

	engine->cameraManager->GetCameraByIndex(0)->SetChild(car);
	CEntityLapCounter* lapCountera = new CEntityLapCounter(engine);
	CEntitySpeedoMeter* speedoMetera = new CEntitySpeedoMeter(engine);
	CEntityPositionCounter* positionCountera = new CEntityPositionCounter(engine);
	speedoMetera->ChangeZIndex(speedoMetera->zIndex + 1);
	speedoMetera->SetChild(car);
	positionCountera->SetCar(car);
	lapCountera->SetLapCountable(car);
	lapCountera->SetCamera(engine->cameraManager->GetCameraByIndex(0));
	speedoMetera->SetCamera(engine->cameraManager->GetCameraByIndex(0));
	positionCountera->SetCamera(engine->cameraManager->GetCameraByIndex(0));

	if (engine->multiPlayer)
	{
		CEntityCar* carb = new CEntityCar(engine, factory->map);
		carb->SetControlScheme(new CPlayer2ControlSchemeCar(engine));
		engine->cameraManager->GetCameraByIndex(1)->SetChild(carb);
		CEntityLapCounter* lapCounterb = new CEntityLapCounter(engine);
		CEntitySpeedoMeter* speedoMeterb = new CEntitySpeedoMeter(engine);
		CEntityPositionCounter* positionCounterb = new CEntityPositionCounter(engine);
		speedoMeterb->ChangeZIndex(speedoMeterb->zIndex + 1);
		speedoMeterb->SetChild(carb);
		positionCounterb->SetCar(carb);
		lapCounterb->SetLapCountable(carb);
		lapCounterb->SetCamera(engine->cameraManager->GetCameraByIndex(1));
		speedoMeterb->SetCamera(engine->cameraManager->GetCameraByIndex(1));
		positionCounterb->SetCamera(engine->cameraManager->GetCameraByIndex(1));
	}

	int spawns = factory->map->availableSpawns.size();
	for (int i = 0; i < spawns; i++)
	{
		CEntityCar* tempCar = new CEntityCar(engine, factory->map);
		tempCar->SetControlScheme(new CAIControlSchemeCar(engine));
	}

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
	delete engine->world;
	engine->world = nullptr;
	delete engine->currentMap;
	engine->currentMap = nullptr;
	engine->cameraManager->ClearAll();
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
	engine->cameraManager->Update();
	engine->entityManager->Tick();
	engine->world->Step(engine->deltaHelper->GetScaledDelta(), 8, 3);
	engine->currentMap->CheckPositions();
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
