#include "CEntitySpeedoMeter.h"
#include "CDrawManager.h"
#include "CMap.h"
#include <iomanip>
#include "CTextureManager.h"

CEntitySpeedoMeter::CEntitySpeedoMeter(CEngine* engine) : CEntity(engine), IInputListener(engine), IDrawListener(engine, (int)CDrawManager::Layers::UI)
{
	this->font = font;
	this->engine = engine;

	meter_texture = engine->textureManager->GetTexture("Images/meter.png");
	angle = 0;
	point = {95, 8};

	speedometer = new CUIImage(engine, "Images/speedometer.png");
	speedometer->SetHorizontalAlignment(EUIALignmentHorizontal::LEFT);
	speedometer->SetVerticalAlignment(EUIALignmentVertical::BOTTOM);

	speedLabel = new CUILabel(engine, "Bangers", "");
	speedLabel->SetHorizontalAlignment(EUIALignmentHorizontal::CENTER);
	speedLabel->SetVerticalAlignment(EUIALignmentVertical::CENTER);
	speedLabel->SetFontSize(50);
	speedLabel->SetPosition(0, 2);

	labelContainer = new CUIContainer(engine);
	labelContainer->SetHorizontalAlignment(EUIALignmentHorizontal::LEFT);
	labelContainer->SetVerticalAlignment(EUIALignmentVertical::BOTTOM);
	labelContainer->SetWidth(141);
	labelContainer->SetHeight(73);
	labelContainer->SetPosition(243, 0);
	labelContainer->AddUIElement(speedLabel);
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
	SDL_Rect backrect = { camera->GetViewPort().x+25, camera->GetViewPort().h - 30, 120, 17};

	SDL_RenderCopyEx(renderer, meter_texture, NULL, &backrect, angle, &point, SDL_FLIP_NONE);
}

void CEntitySpeedoMeter::Input(SDL_Event* event)
{
	if (event->type == SDL_WINDOWEVENT)
	{
		switch (event->window.event)
		{
		case SDL_WINDOWEVENT_RESIZED:
			UpdateContainers();
			break;
		}
	}
}

void CEntitySpeedoMeter::SetChild(IBox2DListener* child)
{
	this->child = child;
}

IBox2DListener* CEntitySpeedoMeter::GetChild()
{
	return child;
}

void CEntitySpeedoMeter::SetCamera(CCamera* camera)
{
	this->camera = camera;
	UpdateContainers();
}

void CEntitySpeedoMeter::UpdateContainers()
{
	speedometer->SetContainer(camera->GetViewPort().x, camera->GetViewPort().y, camera->GetViewPort().w, camera->GetViewPort().h);
	labelContainer->SetContainer(camera->GetViewPort().x, camera->GetViewPort().y, camera->GetViewPort().w, camera->GetViewPort().h);
}
