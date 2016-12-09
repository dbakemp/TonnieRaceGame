#include "CEntityBuild.h"
#include "CDrawManager.h"
#include <iomanip>
#include <chrono>
#include <sstream>

CEntityBuild::CEntityBuild(CEngine * engine) : CEntity(engine), IDrawListener(engine, (int)CDrawManager::Layers::UI), IInputListener(engine)
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
