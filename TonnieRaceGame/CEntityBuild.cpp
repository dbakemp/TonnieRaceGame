#include "CEntityBuild.h"
#include <iomanip>
#include <chrono>
#include <sstream>

CEntityBuild::CEntityBuild(CEngine * engine, TTF_Font * font) : CEntity(engine), IDrawListener(engine), IInputListener(engine)
{
	visible = false;
	tm localTime;
	std::chrono::system_clock::time_point t = std::chrono::system_clock::now();
	time_t now = std::chrono::system_clock::to_time_t(t);
	localtime_s(&localTime, &now);

	std::stringstream buffer;
	buffer << "["
		<< std::setfill('0') << std::setw(2) << localTime.tm_mday << '-'
		<< std::setfill('0') << std::setw(2) << localTime.tm_mon+1 << '-'
		<< std::setfill('0') << std::setw(2) << localTime.tm_year + 1900 << ' '
		<< std::setfill('0') << std::setw(2) << localTime.tm_hour << ':'
		<< std::setfill('0') << std::setw(2) << localTime.tm_min << ':'
		<< std::setfill('0') << std::setw(2) << localTime.tm_sec << "] ";

	text = "Development Build: "+buffer.str();

	this->engine = engine;
	this->font = font;
}

CEntityBuild::~CEntityBuild()
{
}

void CEntityBuild::Update()
{
}

void CEntityBuild::Draw(SDL_Renderer * renderer)
{
	if (!visible) { return; }

	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), { 255, 255, 255 });
	SDL_Texture* texture = SDL_CreateTextureFromSurface(engine->renderer, surface);

	SDL_Rect srect;
	SDL_QueryTexture(texture, NULL, NULL, &srect.w, &srect.h);

	SDL_Rect dstrect = { engine->windowWidth - srect.w - 10, engine->windowHeight - srect.h - 10, srect.w, srect.h };
	SDL_RenderCopy(engine->renderer, texture, NULL, &dstrect);

	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
}

void CEntityBuild::Input(SDL_Event * event)
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
