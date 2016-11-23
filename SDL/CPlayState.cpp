#define _CRT_SECURE_NO_WARNINGS
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
#include "SDL_ttf.h"
#include <iomanip>
#include <ctime>


void CPlayState::init()
{
	return;
}

void CPlayState::init(CEngine* engine)
{
	b2Vec2 gravity(0, 0);

	engine->world = new b2World(gravity);

	SDL_QueryTexture(backmapTexture, NULL, NULL, &texW, &texH);

	CLevelFactory* factory = new CLevelFactory(engine);
	factory->LoadMap("Resources/Maps/map1.json");

	camera = new CCamera();
	camera->windowHeight = 720;
	camera->windowWidth = 1280;

	engine->camera = camera;

	CEntityCar* car = new CEntityCar(engine, factory->map);
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

	if (engine->showFPSCounter) drawFPSCounter(engine);
	

}

void CPlayState::drawFPSCounter(CEngine* engine)
{
	string title = "FPS";
	title.append(": ");
	title.append(to_string(engine->fpsCounter));

	const char* fileString = title.c_str();
	
	time_t t = time(0);   // get time now
	struct tm * now = localtime(&t);

	string dateString = "Development Build: ";
	dateString.append(to_string(now->tm_mday));
	dateString.append("-");
	dateString.append(to_string(now->tm_mon + 1));
	dateString.append("-");
	dateString.append(to_string(now->tm_year + 1900));
	dateString.append(" ");
	dateString.append(to_string(now->tm_hour));
	dateString.append(":");
	dateString.append(to_string(now->tm_min));
	

	const char* titleString = dateString.c_str();

	TTF_Init();
	TTF_Font* fpsFont = TTF_OpenFont("Resources/Fonts/opensans.ttf", 16);
	SDL_Color color = { 255, 255, 255 };
	SDL_Surface* surface = TTF_RenderText_Solid(fpsFont, fileString, color);
	SDL_Surface* titleSurface = TTF_RenderText_Solid(fpsFont, titleString, color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(engine->renderer, surface);
	SDL_Texture* titleTexture = SDL_CreateTextureFromSurface(engine->renderer, titleSurface);


	int texW = 0;
	int texH = 0;
	SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
	SDL_Rect dstrect = { 10, 10, texW, texH };
	SDL_QueryTexture(titleTexture, NULL, NULL, &texW, &texH);
	SDL_Rect titleRect = { 1000, 700, texW, texH };

	SDL_RenderCopy(engine->renderer, texture, NULL, &dstrect);
	SDL_RenderCopy(engine->renderer, titleTexture, NULL, &titleRect);
	SDL_RenderPresent(engine->renderer);

	TTF_CloseFont(fpsFont);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
	TTF_Quit();
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
