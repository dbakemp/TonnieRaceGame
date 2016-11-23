#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "CStateManager.h"
#include "CCamera.h"
#include "CIntroState.h"
#include "CDrawManager.h"
#include "CInputManager.h"
#include <iostream>

void CIntroState::init()
{
	return;
}

void CIntroState::init(CEngine* engine)
{
	TTF_Init();

	TTF_Font* fntPricedown = TTF_OpenFont("Resources/Fonts/pricedown.ttf", 48);

	SDL_Color color = {16, 157, 232};


	SDL_Surface* background = IMG_Load("Resources/Images/mainmenu.jpg");
	SDL_Texture* background_texture = SDL_CreateTextureFromSurface(engine->renderer, background);

	int backW = 0;
	int backH = 0;
	SDL_QueryTexture(background_texture, NULL, NULL, &backW, &backH);
	SDL_Rect backrect = {0,0,backW, backH};

	SDL_RenderCopy(engine->renderer, background_texture, NULL, &backrect);
	SDL_RenderPresent(engine->renderer);

	TTF_CloseFont(fntPricedown);
	TTF_Quit();

	engine->musicHelper->playTrack("music\\title.mp3", false);
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

void CIntroState::handleEvents(CEngine* engine)
{
}

void CIntroState::update(CEngine* engine)
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
			case SDLK_SPACE:
				engine->stateManager->changeState(Playing, engine);
				break;
			case SDLK_1:
				engine->stateManager->changeState(Help, engine);
				break;
			case SDLK_2:
				engine->stateManager->changeState(Credits, engine);
				break;
			case SDLK_3:
				engine->stateManager->changeState(Scores, engine);
				break;
			default:
				break;
			}
		}
		else if (event.type == SDL_CONTROLLERBUTTONDOWN)
		{
			if (event.cbutton.button == SDL_CONTROLLER_BUTTON_A)
			{
				engine->stateManager->changeState(Playing, engine);
			}
		}
		else
		{
			engine->inputManager->Tick(&event);
		}
	}
}

void CIntroState::draw(CEngine* engine)
{
}

CIntroState::CIntroState(CEngine* engine)
{
	init(engine);
}
