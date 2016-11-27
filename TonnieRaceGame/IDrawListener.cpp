#include "IDrawListener.h"
#include "CDrawManager.h"
#include "CEngine.h"

IDrawListener::IDrawListener(CEngine* engine)
{
	this->engine = engine;
	engine->drawManager->AddListener(this);
}

IDrawListener::~IDrawListener()
{
	engine->drawManager->RemoveListener(this);
}
