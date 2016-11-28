#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "CStateManager.h"
#include "CCamera.h"
#include "CCreditsState.h"
#include "CDrawManager.h"
#include "CInputManager.h"
#include <iostream>

void CCreditsState::init()
{
	return;
}

void CCreditsState::init(CEngine* engine)
{
	TTF_Init();

	TTF_Font* fntPricedown = TTF_OpenFont("Resources/Fonts/pricedown.ttf", 48);

	SDL_Color color = { 16, 157, 232 };


	SDL_Surface* background = IMG_Load("Resources/Images/credits.jpg");
	SDL_Texture* background_texture = SDL_CreateTextureFromSurface(engine->renderer, background);

	int backW = 0;
	int backH = 0;
	SDL_QueryTexture(background_texture, NULL, NULL, &backW, &backH);
	SDL_Rect backrect = { 0,0,backW, backH };

	SDL_RenderCopy(engine->renderer, background_texture, NULL, &backrect);
	SDL_RenderPresent(engine->renderer);

	TTF_CloseFont(fntPricedown);
	TTF_Quit();

}

void CCreditsState::clean()
{
}

void CCreditsState::pause()
{
}

void CCreditsState::resume()
{
}

void CCreditsState::handleEvents(CEngine* engine)
{
}

void CCreditsState::update(CEngine* engine)
{
}

void CCreditsState::draw(CEngine* engine)
{
}

void CCreditsState::input(CEngine* engine, SDL_Event * event)
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
	else
	{
		engine->inputManager->Tick(event);
	}
}

CCreditsState::CCreditsState(CEngine* engine)
{
	init(engine);
}
