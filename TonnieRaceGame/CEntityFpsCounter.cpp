#include "CEntityFpsCounter.h"
#include "CDeltaHelper.h"
#include "CDrawManager.h"

CEntityFpsCounter::CEntityFpsCounter(CEngine* engine) : CEntity(engine), IDrawListener(engine, (int)CDrawManager::Layers::UI), IInputListener(engine)
{
	label = new CUILabel(engine, "Bangers", "");
	label->SetPosition(10, 10);
	label->SetFontSize(36);
	label->SetVisibility(true);
	this->engine = engine;
}

CEntityFpsCounter::~CEntityFpsCounter()
{
}

void CEntityFpsCounter::Update()
{
	ticksum -= ticklist[tickindex]; /* subtract value falling off */
	ticksum += 1.0 / engine->deltaHelper->delta; /* add new value */
	ticklist[tickindex] = 1.0 / engine->deltaHelper->delta; /* save new value so it can be subtracted later */
	if (++tickindex == 500) /* inc buffer index */
		tickindex = 0;

	label->SetText("FPS: " + std::to_string(ticksum / 500));
}

void CEntityFpsCounter::Draw(SDL_Renderer* renderer)
{
}

void CEntityFpsCounter::Input(SDL_Event* event)
{
	switch (event->type)
	{
	case SDL_KEYDOWN:
		switch (event->key.keysym.sym)
		{
		case SDLK_q:
			label->ToggleVisibility();
			break;
		}
	}
}
