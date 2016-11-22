#include "SDL.h"
#include "CStateManager.h"
#include "SDL_image.h"
#include "CPlayState.h"
#include "CEngine.h"
#include "CEntityCar.h"
#include "CEntitySmallSquare.h"
#include "CInputManager.h"
#include "CEntityManager.h"
#include "CDrawManager.h"
#include "CLevelFactory.h"

void CPlayState::init()
{
	return;
}

void CPlayState::init(CEngine* engine)
{
	b2Vec2 gravity(0, 0);

	engine->world = new b2World(gravity);

	SDL_Surface * map = IMG_Load("Resources/Maps/map1.png");
	backmapTexture = SDL_CreateTextureFromSurface(engine->renderer, map);

	SDL_QueryTexture(backmapTexture, NULL, NULL, &texW, &texH);

	CLevelFactory* factory = new CLevelFactory(engine);
	factory->LoadMap("Resources/Maps/map1.json");

	camera = new CCamera();
	camera->windowHeight = 720;
	camera->windowWidth = 1280;

	engine->camera = camera;

	CEntityCar* car = new CEntityCar(engine);
	camera->SetChild(car);

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

void CPlayState::handleEvents(CEngine * engine)
{
}

void CPlayState::update(CEngine *engine)
{
	SDL_Event event;

	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT) {
			engine->running = false;
			SDL_Quit();
		}
		else {
			engine->inputManager->Tick(&event);
		}
	}

	SDL_SetRenderDrawColor(engine->renderer, 0, 0, 0, 255);
	SDL_RenderClear(engine->renderer);

	engine->entityManager->Tick();
	engine->world->Step(0.016f, 8, 3);
	camera->Update();

	SDL_Rect dstrect = {-engine->camera->posX, -engine->camera->posY, texW, texH };
	SDL_RenderCopy(engine->renderer, backmapTexture, NULL, &dstrect);
	engine->drawManager->Tick(engine->renderer);
}

void CPlayState::draw(CEngine * engine)
{
}

CPlayState::CPlayState(CEngine * engine)
{
	init(engine);
}

CPlayState::~CPlayState()
{
	clean();
}
