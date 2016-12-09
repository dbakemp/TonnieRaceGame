#include "CEntityLapCounter.h"
#include "CDrawManager.h"
#include <string.h>
#include "CMap.h"
#include "EUIAlignment.h"

CEntityLapCounter::CEntityLapCounter(CEngine* engine) : CEntity(engine)
{
	label = new CUILabel(engine, "Bangers", "");
	label->SetPosition(-10, 10);
	label->SetHorizontalAlignment(EUIALignmentHorizontal::RIGHT);
	label->SetFontSize(30);

	this->engine = engine;
}

CEntityLapCounter::~CEntityLapCounter()
{

}

void CEntityLapCounter::Update()
{
	label->SetText("Lap:" + std::to_string(lapCountable->currentLap + 1) + "/" + std::to_string(engine->currentMap->laps));
}

void CEntityLapCounter::SetLapCountable(ILapCountable* lapCountable)
{
	this->lapCountable = lapCountable;
}

ILapCountable* CEntityLapCounter::GetLapCountable()
{
	return lapCountable;
}
