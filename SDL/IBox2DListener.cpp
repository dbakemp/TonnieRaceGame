#include "IBox2DListener.h"
#include "CBox2DManager.h"
#include "CEngine.h"

IBox2DListener::IBox2DListener(CEngine *engine)
{
	this->engine = engine;
	engine->box2DManager->AddListener(this);
}

IBox2DListener::~IBox2DListener()
{
	engine->box2DManager->RemoveListener(this);
}
