#define _CRT_SECURE_NO_WARNINGS
#include "SDL.h"
#include "CStateManager.h"
#include "SDL_image.h"
#include "CGAState.h"
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
#include <functional>

void CGAState::init(CEngine* engine)
{
	SDL_Renderer* renderer;
	renderer = SDL_CreateRenderer(engine->window, -1, 0);
	SDL_RenderClear(renderer);

	TTF_Init();
	TTF_Font* fpsFont = TTF_OpenFont("Resources/Fonts/opensans.ttf", 16);
	TTF_Font* kmhFont = TTF_OpenFont("Resources/Fonts/opensans.ttf", 64);

	b2Vec2 gravity(0, 0);

	engine->world = new b2World(gravity);

	engine->world->SetContactListener(engine->collisionHelper);

	SDL_QueryTexture(backmapTexture, NULL, NULL, &texW, &texH);

	CLevelFactory* factory = new CLevelFactory(engine);

	CDebugLogger::PrintDebug("Loading GA");
	factory->LoadMap("Resources/Maps/mapGA.json");

	engine->currentMap = factory->map;

	camera = new CCamera(engine);

	engine->camera = camera;

	CEntityCarAI* car = new CEntityCarAI(engine, factory->map);

	car->SetFinishCallback(std::bind(&CGAState::OnFinish, this, std::placeholders::_1));
	camera->SetChild(car);

	CEntityFpsCounter* fpsCounter = new CEntityFpsCounter(engine, fpsFont);
	CEntityBuild* build = new CEntityBuild(engine, fpsFont);

	this->engine = engine;
}

void CGAState::clean(CEngine* engine)
{
	engine->drawManager->Clear();
	engine->inputManager->Clear();
	engine->box2DManager->Clear();
	engine->entityManager->Clear();

	delete camera;
	camera = nullptr;
}

void CGAState::pause()
{
}

void CGAState::resume()
{
}

void CGAState::handleEvents(CEngine* engine)
{
}

void CGAState::update(CEngine* engine)
{
	GATicks++;
	engine->deltaHelper->delta *= 10;
	camera->Update();
	engine->entityManager->Tick();
	engine->world->Step(engine->deltaHelper->delta, 8, 3);
}

void CGAState::draw(CEngine* engine)
{
	SDL_SetRenderDrawColor(engine->renderer, 0, 0, 0, 255);
	SDL_RenderClear(engine->renderer);
	engine->drawManager->Tick(engine->renderer);
}

void CGAState::input(CEngine* engine, SDL_Event * event)
{
	engine->inputManager->Tick(event);
}

void CGAState::OnFinish(IBox2DListener* call)
{
	CDebugLogger::PrintDebug(std::to_string(GATicks));
	GATicks = 0;

	CEntityCarAI* car = new CEntityCarAI(engine, engine->currentMap);

	car->SetFinishCallback(std::bind(&CGAState::OnFinish, this, std::placeholders::_1));
	camera->SetChild(car);
}

CGAState::CGAState(CEngine* engine)
{
	init(engine);
}
