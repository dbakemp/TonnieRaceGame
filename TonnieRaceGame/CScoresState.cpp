#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "CStateManager.h"
#include "CCamera.h"
#include "CScoresState.h"
#include "CDrawManager.h"
#include "CInputManager.h"
#include <iostream>

void CScoresState::init()
{
	return;
}

void CScoresState::init(CEngine* engine)
{
	TTF_Init();

	TTF_Font* fntPricedown = TTF_OpenFont("Resources/Fonts/pricedown.ttf", 48);

	SDL_Color color = { 16, 157, 232 };


	SDL_Surface* background = IMG_Load("Resources/Images/highscores.jpg");
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

void CScoresState::clean()
{
}

void CScoresState::pause()
{
}

void CScoresState::resume()
{
}

void CScoresState::handleEvents(CEngine* engine)
{
}

void CScoresState::update(CEngine* engine)
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
		else if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			int mouseX = event.motion.x;
			int mouseY = event.motion.y;
			switch (event.button.button)
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
			break;
		}
		else
		{
			engine->inputManager->Tick(&event);
		}
	}
}

void CScoresState::draw(CEngine* engine)
{
}

CScoresState::CScoresState(CEngine* engine)
{
	init(engine);
}