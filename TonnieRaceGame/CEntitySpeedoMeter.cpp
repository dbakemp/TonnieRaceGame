#include "CEntitySpeedoMeter.h"
#include "CDrawManager.h"
#include <string.h>
#include "CMap.h"
#include "CDebugLogger.h"
#include <iomanip>

CEntitySpeedoMeter::CEntitySpeedoMeter(CEngine* engine, TTF_Font* font) : CEntity(engine), IDrawListener(engine, (int)CDrawManager::Layers::UI)
{
	this->font = font;
	this->engine = engine;
}

CEntitySpeedoMeter::~CEntitySpeedoMeter()
{

}

void CEntitySpeedoMeter::Update()
{
	float32 speed = GetChild()->body->GetLinearVelocity().Length();

	std::stringstream ss;
	ss << std::fixed << std::setprecision(0) << speed;
	std::string speedRounded = ss.str();

	text = "Speed: " + speedRounded + " km/h";
}

void CEntitySpeedoMeter::Draw(SDL_Renderer* renderer)
{
	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), { 255, 255, 255 });
	SDL_Texture* texture = SDL_CreateTextureFromSurface(engine->renderer, surface);

	SDL_Rect srect;
	SDL_QueryTexture(texture, NULL, NULL, &srect.w, &srect.h);

	SDL_Rect dstrect = { engine->windowWidth - srect.w - 10, engine->windowHeight - srect.h - 10, srect.w, srect.h };
	SDL_RenderCopy(engine->renderer, texture, NULL, &dstrect);

	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
}

void CEntitySpeedoMeter::SetChild(IBox2DListener* child)
{
	this->child = child;
}

IBox2DListener* CEntitySpeedoMeter::GetChild()
{
	return child;
}