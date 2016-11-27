#include "CEntityLapCounter.h"
#include <string.h>
#include "CMap.h"

CEntityLapCounter::CEntityLapCounter(CEngine* engine, TTF_Font* font) : CEntity(engine), IDrawListener(engine)
{
	this->font = font;
	this->engine = engine;
}

CEntityLapCounter::~CEntityLapCounter()
{

}

void CEntityLapCounter::Update()
{
	text = "Lap:" + std::to_string(lapCountable->currentLap+1) + "/" + std::to_string(engine->currentMap->laps);
}

void CEntityLapCounter::Draw(SDL_Renderer* renderer)
{
	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), { 255, 255, 255 });
	SDL_Texture* texture = SDL_CreateTextureFromSurface(engine->renderer, surface);

	SDL_Rect srect;
	SDL_QueryTexture(texture, NULL, NULL, &srect.w, &srect.h);

	SDL_Rect dstrect = { engine->windowWidth - srect.w - 10, 10, srect.w, srect.h };
	SDL_RenderCopy(engine->renderer, texture, NULL, &dstrect);

	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
}

void CEntityLapCounter::SetLapCountable(ILapCountable* lapCountable)
{
	this->lapCountable = lapCountable;
}

ILapCountable* CEntityLapCounter::GetLapCountable()
{
	return lapCountable;
}
