#include "CEntityFpsCounter.h"
#include "CDeltaHelper.h"
#include "CDrawManager.h"

CEntityFpsCounter::CEntityFpsCounter(CEngine * engine, TTF_Font * font) : CEntity(engine), IDrawListener(engine, (int)CDrawManager::Layers::UI), IInputListener(engine)
{
	visible = false;
	this->engine = engine;
	this->font = font;
}

CEntityFpsCounter::~CEntityFpsCounter()
{
}

void CEntityFpsCounter::Update()
{
	ticksum -= ticklist[tickindex];  /* subtract value falling off */
	ticksum += 1.0/engine->deltaHelper->delta;              /* add new value */
	ticklist[tickindex] = 1.0 / engine->deltaHelper->delta;   /* save new value so it can be subtracted later */
	if (++tickindex == 1000)    /* inc buffer index */
		tickindex = 0;

	text = "FPS: "+std::to_string(ticksum / 1000);
}

void CEntityFpsCounter::Draw(SDL_Renderer * renderer)
{
	if (!visible) { return; }

	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), { 255, 255, 255 });
	SDL_Texture* texture = SDL_CreateTextureFromSurface(engine->renderer, surface);

	SDL_Rect srect;
	SDL_QueryTexture(texture, NULL, NULL, &srect.w, &srect.h);

	SDL_Rect dstrect = { 10, 10, srect.w, srect.h };
	SDL_RenderCopy(engine->renderer, texture, NULL, &dstrect);

	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
}

void CEntityFpsCounter::Input(SDL_Event * event)
{
	switch (event->type)
	{
	case SDL_KEYDOWN:
		switch (event->key.keysym.sym)
		{
		case SDLK_f:
			visible = !visible;
			break;
		}
	}
}
