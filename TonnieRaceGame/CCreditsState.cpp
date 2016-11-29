#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "CStateManager.h"
#include "CCamera.h"
#include "CCreditsState.h"
#include "CDrawManager.h"
#include "CInputManager.h"
#include "CDebugLogger.h"
#include <iostream>

#include <stdio.h>
#include <stdlib.h>

#include <vlc/vlc.h>


void CCreditsState::init()
{
	return;
}

void CCreditsState::init(CEngine* engine)
{
	//TTF_Init();

	//TTF_Font* fntPricedown = TTF_OpenFont("Resources/Fonts/pricedown.ttf", 48);

	//SDL_Color color = { 16, 157, 232 };


	//SDL_Surface* background = IMG_Load("Resources/Images/credits.jpg");
	//SDL_Texture* background_texture = SDL_CreateTextureFromSurface(engine->renderer, background);

	//int backW = 0;
	//int backH = 0;
	//SDL_QueryTexture(background_texture, NULL, NULL, &backW, &backH);
	//SDL_Rect backrect = { 0,0,backW, backH };

	//SDL_RenderCopy(engine->renderer, background_texture, NULL, &backrect);
	//SDL_RenderPresent(engine->renderer);

	//TTF_CloseFont(fntPricedown);
	//TTF_Quit();

	char const *vlc_argv[] =
	{
		"--width=100",
		"--height=100",
		"--no-embedded-video", "--no-video-deco",
	};
	int vlc_argc = sizeof(vlc_argv) / sizeof(*vlc_argv);

	CDebugLogger::PrintDebug("Init VLC");
	/* Load the VLC engine */
	inst = libvlc_new(vlc_argc, vlc_argv);

	// create a new item
	m = libvlc_media_new_path(inst, "Resources\\Videos\\outro.mp4");

	// create a media play playing environment
	mp = libvlc_media_player_new_from_media(m);

	libvlc_video_set_format(mp, "RV16", 100, 100, 200);

	CDebugLogger::PrintDebug("Releasing media file");
	// no need to keep the media now
	libvlc_media_release(m);

	CDebugLogger::PrintDebug("Start playing video");
	// play the media_player
	libvlc_media_player_play(mp);



	//Wait 40 secs, length of the outro video
	Sleep(40000);

	CDebugLogger::PrintDebug("Stop playing video");
	// stop playing
	libvlc_media_player_stop(mp);

	CDebugLogger::PrintDebug("Releasing mediaplayer");
	// free the media_player
	libvlc_media_player_release(mp);

	CDebugLogger::PrintDebug("Release VLC");
	libvlc_release(inst);
	
	CDebugLogger::PrintDebug("Changing state to menu");
	engine->stateManager->changeState(Menu, engine);

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
