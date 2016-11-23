#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "CStateManager.h"
#include "CCamera.h"
#include "CHelpState.h"
#include "CDrawManager.h"
#include "CInputManager.h"
#include <iostream>

void CHelpState::init()
{
	return;
}

void CHelpState::init(CEngine* engine)
{

	SDL_Surface* background = IMG_Load("Resources/Images/help.jpg");
	SDL_Texture* background_texture = SDL_CreateTextureFromSurface(engine->renderer, background);


	int backW = 0;
	int backH = 0;
	SDL_QueryTexture(background_texture, NULL, NULL, &backW, &backH);
	SDL_Rect backrect = { 0,0,backW, backH };

	SDL_RenderCopy(engine->renderer, background_texture, NULL, &backrect);
	SDL_RenderPresent(engine->renderer);

	engine->musicHelper->playTrack("music\\plingplongplong.mp3", false);
}

void CHelpState::clean()
{
}

void CHelpState::pause()
{
}

void CHelpState::resume()
{
}

void CHelpState::handleEvents(CEngine* engine)
{
}

void CHelpState::update(CEngine* engine)
{
	SDL_Event event;

	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
		{
			engine->running = false;
			SDL_Quit();
		}
		else if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				engine->stateManager->changeState(Menu, engine);
				break;
			default:
				break;
			}
		}
		else
		{
			engine->inputManager->Tick(&event);
		}
	}
}

void CHelpState::draw(CEngine* engine)
{
}

CHelpState::CHelpState(CEngine* engine)
{
	init(engine);
}
