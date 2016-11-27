#define _CRT_SECURE_NO_DEPRECATE
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

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
	size_t written = fwrite(ptr, size, nmemb, stream);
	return written;
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

	CURL *curl;
	FILE *fp;
	CURLcode res;

	FILE *file;
	int file_exists;
	const char * filename = "ads\\my_file.png";

	/*first check if the file exists...*/
	file = fopen(filename, "r");
	if (file == NULL) file_exists = 0;
	else { file_exists = 1; fclose(file); }

	/*...then open it in the appropriate way*/
	if (file_exists == 1)
	{
		printf("file exists!\n");
		file = fopen(filename, "r+b");
	}
	else
	{
		printf("file does not exist!\n");
		file = fopen(filename, "w+b");
	}

	if (file != NULL)
	{
		printf("file opened succesfully!\n");
		fclose(file);
	}

	char *url = "http://localhost/marketing/uploads/20161127181139.png";
	//char outfilename[FILENAME_MAX] = "C:\Users\Tim\Desktop\Desktop\School\bbb.png";
	curl = curl_easy_init();
	if (curl) {
		fp = fopen(filename, "wb");
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
		res = curl_easy_perform(curl);
		/* always cleanup */
		curl_easy_cleanup(curl);
		fclose(fp);
	}
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

void CHelpState::draw(CEngine* engine)
{
}

CHelpState::CHelpState(CEngine* engine)
{
	init(engine);
}
