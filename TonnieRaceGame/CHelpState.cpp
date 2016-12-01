#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "CStateManager.h"
#include "CCamera.h"
#include "CHelpState.h"
#include "CDrawManager.h"
#include "CInputManager.h"
#include <iostream>
#include <curl/curl.h>
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
}

void CHelpState::draw(CEngine* engine)
{
}

void CHelpState::input(CEngine* engine, SDL_Event * event)
{
	if (event->type == SDL_KEYDOWN)
	{
		switch (event->key.keysym.sym)
		{
		case SDLK_ESCAPE:
			engine->stateManager->changeState(Menu, engine);
			break;
		default:
			break;
		}
	}
	else if (event->type == SDL_MOUSEBUTTONDOWN)
	{
		int mouseX = event->motion.x;
		int mouseY = event->motion.y;
		switch (event->button.button)
		{
		case SDL_BUTTON_LEFT:
			if (mouseX > 35 && mouseX < 123 && mouseY > 650 && mouseY < 702)
			{
				engine->stateManager->changeState(Menu, engine);
			}

			break;
		default:
			break;
		}
	}
	else if (event->type == SDL_CONTROLLERBUTTONDOWN)
	{
		if (event->cbutton.button == SDL_CONTROLLER_BUTTON_A || event->cbutton.button == SDL_CONTROLLER_BUTTON_B)
		{
			engine->stateManager->changeState(Menu, engine);
		}
	}
	else
	{
		engine->inputManager->Tick(event);
	}
}

CHelpState::CHelpState(CEngine* engine)
{
	init(engine);
}
