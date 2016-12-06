#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "CStateManager.h"
#include "CCamera.h"
#include "CIntroState.h"
#include "CDrawManager.h"
#include "CInputManager.h"
#include <iostream>
#include "CDebugLogger.h"

void CIntroState::init(CEngine* engine)
{
	selectedItem = 0;
	lastState = 0;

	TTF_Init();

	TTF_Font* fntPricedown = TTF_OpenFont("Resources/Fonts/pricedown.ttf", 48);

	SDL_Color color = {16, 157, 232};

	background = IMG_Load("Resources/Images/mainmenu.jpg");
	if (engine->gameControllerConnected)
	{
		background = IMG_Load("Resources/Images/spelen-selected.jpg");
	}
	SDL_Texture* background_texture = SDL_CreateTextureFromSurface(engine->renderer, background);

	int backW = 0;
	int backH = 0;
	SDL_QueryTexture(background_texture, NULL, NULL, &backW, &backH);
	SDL_Rect backrect = {0,0,backW, backH};

	SDL_RenderCopy(engine->renderer, background_texture, NULL, &backrect);

	TTF_CloseFont(fntPricedown);
	TTF_Quit();

	//adHelper = new AdHelper();
}

void CIntroState::clean(CEngine* engine)
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
	if (engine->gameControllerConnected)
	{
		switch (selectedItem)
		{
		case 0:
			if (lastState != selectedItem)
				background = IMG_Load("Resources/Images/spelen-selected.jpg");
			break;
		case 1:
			if (lastState != selectedItem)
				background = IMG_Load("Resources/Images/help-selected.jpg");
			break;
		case 2:
			if (lastState != selectedItem)
				background = IMG_Load("Resources/Images/highscores-selected.jpg");
			break;
		case 3:
			if (lastState != selectedItem)
				background = IMG_Load("Resources/Images/credits-selected.jpg");
			break;
		default:
			break;
		}

		if (lastState != selectedItem)
		{
			SDL_Texture* background_texture = SDL_CreateTextureFromSurface(engine->renderer, background);

			int backW = 0;
			int backH = 0;
			SDL_QueryTexture(background_texture, NULL, NULL, &backW, &backH);
			SDL_Rect backrect = { 0,0,backW, backH };

			SDL_RenderCopy(engine->renderer, background_texture, NULL, &backrect);
		}

		lastState = selectedItem;
	}
}

void CIntroState::draw(CEngine* engine)
{

}

void CIntroState::input(CEngine* engine, SDL_Event * event)
{
	if (event->type == SDL_KEYDOWN)
	{
		switch (event->key.keysym.sym)
		{
		case SDLK_SPACE:
			engine->stateManager->changeState(Playing, engine);
			break;
		case SDLK_RIGHT:
			SelectRight();
			break;
		case SDLK_LEFT:
			SelectLeft();
			break;
		case SDLK_KP_ENTER:
		case 13:
			SelectOption(engine);
			break;
		default:
			break;
		}
	}
	else if (event->type == SDL_MOUSEMOTION)
	{
		int mouseX = event->motion.x;
		int mouseY = event->motion.y;

		if (mouseX > 240 && mouseX < 384 && mouseY > 615 && mouseY < 672)
		{
			selectedItem = 0;
		}
		else if (mouseX > 451 && mouseX < 597 && mouseY > 615 && mouseY < 672)
		{
			selectedItem = 1;
		}
		else if (mouseX > 663 && mouseX < 809 && mouseY > 615 && mouseY < 672)
		{
			selectedItem = 2;
		}
		else if (mouseX > 896 && mouseX < 1042 && mouseY > 615 && mouseY < 672)
		{
			selectedItem = 3;
		}

	}
	else if (event->type == SDL_MOUSEBUTTONDOWN)
	{
		int mouseX = event->motion.x;
		int mouseY = event->motion.y;
		switch (event->button.button)
		{
		case SDL_BUTTON_LEFT:
			if (mouseX > 240 && mouseX < 384 && mouseY > 615 && mouseY < 672)
			{
				engine->stateManager->changeState(Playing, engine);
			}
			else if (mouseX > 451 && mouseX < 597 && mouseY > 615 && mouseY < 672)
			{
				engine->stateManager->changeState(Help, engine);
			}
			else if (mouseX > 663 && mouseX < 809 && mouseY > 615 && mouseY < 672)
			{
				engine->stateManager->changeState(Scores, engine);
			}
			else if (mouseX > 896 && mouseX < 1042 && mouseY > 615 && mouseY < 672)
			{
				engine->stateManager->changeState(Credits, engine);
			}
			break;
		default:
			break;
		}
	}
	else if (event->type == SDL_CONTROLLERBUTTONDOWN)
	{
		if (event->cbutton.button == SDL_CONTROLLER_BUTTON_A)
		{
			//engine->stateManager->changeState(Playing, engine);
			SelectOption(engine);
		}
		else if (event->cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_LEFT)
		{
			SelectLeft();
		}
		else if (event->cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT)
		{
			SelectRight();
		}
	}
	else
	{
		engine->inputManager->Tick(event);
	}
}

void CIntroState::SelectLeft()
{
	switch (selectedItem)
	{
	case 0:
		selectedItem = 3;
		break;
	case 1:
		selectedItem = 0;
		break;
	case 2:
		selectedItem = 1;
		break;
	case 3:
		selectedItem = 2;
		break;
	default:
		break;
	}
}

void CIntroState::SelectRight()
{
	switch (selectedItem)
	{
	case 0:
		selectedItem = 1;
		break;
	case 1:
		selectedItem = 2;
		break;
	case 2:
		selectedItem = 3;
		break;
	case 3:
		selectedItem = 0;
		break;
	default:
		break;
	}
}

void CIntroState::SelectOption(CEngine* engine)
{
	switch (selectedItem)
	{
	case 0:
		engine->stateManager->changeState(Playing, engine);
		break;
	case 1:
		engine->stateManager->changeState(Help, engine);
		break;
	case 2:
		engine->stateManager->changeState(Scores, engine);
		break;
	case 3:
		engine->stateManager->changeState(Credits, engine);
		break;
	default:
		break;
	}
}

CIntroState::CIntroState(CEngine* engine)
{
	init(engine);
}
