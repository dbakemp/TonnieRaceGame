#include "CEntitySpeedoMeter.h"
#include "CDrawManager.h"
#include <string.h>
#include "CMap.h"
#include "CDebugLogger.h"
#include <iomanip>

#include "SDL_image.h"

CEntitySpeedoMeter::CEntitySpeedoMeter(CEngine* engine, TTF_Font* font) : CEntity(engine), IDrawListener(engine, (int)CDrawManager::Layers::UI)
{
	this->font = font;
	this->engine = engine;

	meter = IMG_Load("Resources/Images/meter.png");
	meterback = IMG_Load("Resources/Images/meterback.png");
	meter_texture = SDL_CreateTextureFromSurface(engine->renderer, meter);
	meterback_texture = SDL_CreateTextureFromSurface(engine->renderer, meterback);
	angle = 0;
	point = { 95, 8 };
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

	angle = speed;
}

void CEntitySpeedoMeter::Draw(SDL_Renderer* renderer)
{
	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), { 255, 255, 255 });
	SDL_Texture* texture = SDL_CreateTextureFromSurface(engine->renderer, surface);

	SDL_Rect srect;
	SDL_QueryTexture(texture, NULL, NULL, &srect.w, &srect.h);

	SDL_Rect dstrect = { engine->windowWidth - srect.w - 10, srect.h + 20, srect.w, srect.h };
	SDL_RenderCopy(engine->renderer, texture, NULL, &dstrect);

	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
	int backW = 0;
	int backH = 0;
	SDL_QueryTexture(meter_texture, NULL, NULL, 0, 0);
	SDL_Rect backrect = { 87, 702, 120, 17 };
	SDL_Rect meterbackrect = { 0, 550, 350, 171 };

	
	SDL_RenderCopy(engine->renderer, meterback_texture, NULL, &meterbackrect);
	SDL_RenderCopyEx(engine->renderer, meter_texture, NULL, &backrect, angle, &point, SDL_FLIP_NONE);
}

void CEntitySpeedoMeter::SetChild(IBox2DListener* child)
{
	this->child = child;
}

IBox2DListener* CEntitySpeedoMeter::GetChild()
{
	return child;
}