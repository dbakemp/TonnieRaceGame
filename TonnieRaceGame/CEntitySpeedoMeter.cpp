#include "CEntitySpeedoMeter.h"
#include "CDrawManager.h"
#include <string.h>
#include "CMap.h"
#include "CDebugLogger.h"
#include <iomanip>
#include "CTextureManager.h"


#include "SDL_image.h"

CEntitySpeedoMeter::CEntitySpeedoMeter(CEngine* engine, TTF_Font* font) : CEntity(engine), IDrawListener(engine, (int)CDrawManager::Layers::UI)
{
	this->font = font;
	this->engine = engine;

	meter_texture = engine->textureManager->GetTexture("meter.png");
	meterback_texture = engine->textureManager->GetTexture("speedometer.png");
	angle = 0;
	point = { 95, 8 };

	speedLabel = new CUILabel(engine, "Bangers", "");
	speedLabel->SetPosition(280, -5);
	speedLabel->SetHorizontalAlignment(EUIALignmentHorizontal::LEFT);
	speedLabel->SetVerticalAlignment(EUIALignmentVertical::BOTTOM);
	speedLabel->SetFontSize(50);

}

CEntitySpeedoMeter::~CEntitySpeedoMeter()
{

}

void CEntitySpeedoMeter::Update()
{
	float32 speed = GetChild()->body->GetLinearVelocity().Length();

	ticksum -= ticklist[tickindex];
	ticksum += speed;
	ticklist[tickindex] = speed;
	if (++tickindex == 200)
		tickindex = 0;

	std::stringstream ss;
	ss << std::fixed << std::setprecision(0) << ticksum / 200;
	std::string speedRounded = ss.str();

	speedLabel->SetText(speedRounded);
	angle = ticksum / 200;
}

void CEntitySpeedoMeter::Draw(SDL_Renderer* renderer)
{
	int backW = 0;
	int backH = 0;
	SDL_QueryTexture(meter_texture, NULL, NULL, 0, 0);
	SDL_Rect backrect = { 25,  engine->windowHeight-30, 120, 17 };
	
	SDL_Rect meterbackrect = { 0, engine->windowHeight - 132, 383, 132 };
	
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