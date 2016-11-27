#include "IDrawListener.h"
#include "CDrawManager.h"
#include "CEngine.h"

IDrawListener::IDrawListener(CEngine* engine, int zIndex)
{
	this->zIndex = zIndex;
	this->engine = engine;
	engine->drawManager->AddListener(this, zIndex);
}

IDrawListener::~IDrawListener()
{
	engine->drawManager->RemoveListener(this);
}

void IDrawListener::ChangeZIndex(int index)
{
	engine->drawManager->ChangeZIndex(this, index);
}
