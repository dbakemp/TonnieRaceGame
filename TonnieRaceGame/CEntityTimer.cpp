#include "CEntityTimer.h"
#include "CDrawManager.h"
#include "CTimerHelper.h"

CEntityTimer::CEntityTimer(CEngine * engine) : CEntity(engine), IDrawListener(engine, (int)CDrawManager::Layers::UI), IInputListener(engine)
{
	label = new CUILabel(engine, "Bangers", "");
	label->SetPosition(0, 10);
	label->SetFontSize(50);
	label->SetHorizontalAlignment(EUIALignmentHorizontal::CENTER);
	label->SetVisibility(true);

	this->engine = engine;
}

CEntityTimer::~CEntityTimer()
{
}

void CEntityTimer::Update()
{
	label->SetText(engine->timerHelper->Lap());
}

void CEntityTimer::Draw(SDL_Renderer * renderer)
{
}

void CEntityTimer::Input(SDL_Event * event)
{
}
