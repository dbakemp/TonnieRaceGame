#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "CStateManager.h"
#include "CCamera.h"
#include "CIntroState.h"
#include "CDrawManager.h"
#include "CInputManager.h"
#include <iostream>

void CIntroState::init() {
	return;
}

void CIntroState::init(CEngine *engine)
{
	TTF_Init();

	TTF_Font *fntPricedown = TTF_OpenFont("fonts\\pricedown.ttf", 48);

	SDL_Color color = { 16, 157, 232 };
	SDL_Surface * surface = TTF_RenderText_Solid(fntPricedown,
		"Tonnie's grote racewereld!", color);

	SDL_Texture * texture = SDL_CreateTextureFromSurface(engine->renderer, surface);

	SDL_Surface * background = IMG_Load("images\\mainbackground.png");
	SDL_Texture * background_texture = SDL_CreateTextureFromSurface(engine->renderer, background);

	int texW = 0;
	int texH = 0;
	SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
	SDL_Rect dstrect = { 100, 50, texW, texH };

	int backW = 0;
	int backH = 0;
	SDL_QueryTexture(background_texture, NULL, NULL, &backW, &backH);
	SDL_Rect backrect = { 0,0,backW, backH };

	SDL_RenderCopy(engine->renderer, background_texture, NULL, &backrect);
	SDL_RenderCopy(engine->renderer, texture, NULL, &dstrect);
	SDL_RenderPresent(engine->renderer);

	TTF_CloseFont(fntPricedown);

	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
	TTF_Quit();

	engine->musicHelper->playSingleTrack("music\\title.mp3");
}

void CIntroState::clean()
{
}

void CIntroState::pause()
{
}

void CIntroState::resume()
{
}

void CIntroState::handleEvents(CEngine * engine)
{
}

void CIntroState::update(CEngine * engine)
{
	SDL_Event event;

	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT) {
			engine->running = false;
			SDL_Quit();
		}
		else if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_SPACE:
				std::cout << "next";
				engine->stateManager->changeState(Playing, engine);
				break;
			default:
				break;
			}
		}
		else {
			
			engine->inputManager->Tick(&event);
		}
	}

	//SDL_SetRenderDrawColor(engine->renderer, 0, 0, 0, 255);
	//SDL_RenderClear(engine->renderer);

	//engine->drawManager->Tick(engine->renderer);
}

void CIntroState::draw(CEngine * engine)
{
}

CIntroState::CIntroState(CEngine * engine)
{
	init(engine);
}
