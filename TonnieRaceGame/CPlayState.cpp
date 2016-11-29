#define _CRT_SECURE_NO_WARNINGS
#include "SDL.h"
#include "CStateManager.h"
#include "SDL_image.h"
#include "CPlayState.h"
#include "CEngine.h"
#include "CEntityCarAI.h"
#include "CEntitySmallSquare.h"
#include "CEntityBuild.h"
#include "CInputManager.h"
#include "CEntityManager.h"
#include "CDeltaHelper.h"
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
	engine->currentMap = factory->map;

	camera = new CCamera(engine);

	engine->camera = camera;

	CEntityCarAI* car = new CEntityCarAI(engine, factory->map);
	camera->SetChild(car);

	CEntityFpsCounter* fpsCounter = new CEntityFpsCounter(engine, fpsFont);
	CEntityBuild* build = new CEntityBuild(engine, fpsFont);
	CEntityLapCounter* lapCounter = new CEntityLapCounter(engine, fpsFont);
	lapCounter->SetLapCountable(car);

	engine->musicHelper->playTrack("music\\beep.mp3", true);
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
	SDL_SetRenderDrawColor(engine->renderer, 0, 0, 0, 255);
	SDL_RenderClear(engine->renderer);

	engine->entityManager->Tick();
	engine->world->Step(engine->deltaHelper->delta, 8, 3);
	camera->Update();

	engine->drawManager->Tick(engine->renderer);
}

void CPlayState::draw(CEngine* engine)
{
}

void CPlayState::input(CEngine* engine, SDL_Event * event)
{
	engine->inputManager->Tick(event);
}

CPlayState::CPlayState(CEngine* engine)
{
	init(engine);
}

CPlayState::~CPlayState()
{
	clean();
}
