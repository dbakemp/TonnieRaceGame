#include "CEntityBuild.h"
#include "CDrawManager.h"
#include <iomanip>
#include <chrono>
#include <sstream>

#define _MAJOR 0
#define _MINOR 1
#define _BUILD 37

CEntityBuild::CEntityBuild(CEngine * engine) : CEntity(engine), IDrawListener(engine, (int)CDrawManager::Layers::UI), IInputListener(engine)
{
	visible = false;

	text = "Development Build: ["+std::to_string(_MAJOR)+"."+ std::to_string(_MINOR) +"."+ std::to_string(_BUILD)+"]";


	label = new CUILabel(engine, "Bangers", "");
	label->SetPosition(-10, -10);
	label->SetFontSize(20);
	label->SetHorizontalAlignment(EUIALignmentHorizontal::RIGHT);
	label->SetVerticalAlignment(EUIALignmentVertical::BOTTOM);
	label->SetVisibility(false);
	label->SetText(text);

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
}

void CEntityBuild::Input(SDL_Event * event)
{
	switch (event->type)
	{
	case SDL_KEYDOWN:
		switch (event->key.keysym.sym)
		{
		case SDLK_f:
			label->ToggleVisibility();
			break;
		}
	}
}
