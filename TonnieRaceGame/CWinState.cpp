#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "CStateManager.h"
#include "CCamera.h"
#include "CWinState.h"
#include "CDrawManager.h"
#include "CInputManager.h"
#include <iostream>

void CWinState::init()
{
	return;
}

void CWinState::init(CEngine* engine)
{
	engine->musicHelper->stopAll();
	engine->musicHelper->playTrack("music\\daargaatze.mp3", true);
}

void CWinState::clean()
{
}

void CWinState::pause()
{
}

void CWinState::resume()
{
}

void CWinState::handleEvents(CEngine* engine)
{
}

void CWinState::update(CEngine* engine)
{
	SDL_Event event;

	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
		{
			engine->running = false;
			SDL_Quit();
		}
	}

	TTF_Font* font = TTF_OpenFont("Resources/Fonts/opensans.ttf", 120);
	SDL_Surface* surface = TTF_RenderText_Solid(font, "WINNER", { 255, 255, 255 });
	SDL_Texture* texture = SDL_CreateTextureFromSurface(engine->renderer, surface);

	SDL_Rect srect;
	SDL_QueryTexture(texture, NULL, NULL, &srect.w, &srect.h);

	SDL_Rect dstrect = { (engine->windowWidth / 2) - (srect.w / 2), (engine->windowHeight / 2) - (srect.h / 2), srect.w, srect.h };
	SDL_RenderCopy(engine->renderer, texture, NULL, &dstrect);

	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
}

void CWinState::draw(CEngine* engine)
{
}

CWinState::CWinState(CEngine* engine)
{
	init(engine);
}
