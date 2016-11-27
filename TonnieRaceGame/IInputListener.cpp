#include "IInputListener.h"
#include "CInputManager.h"
#include "CEngine.h"

IInputListener::IInputListener(CEngine* engine)
{
	this->engine = engine;
	engine->inputManager->AddListener(this);
}

IInputListener::~IInputListener()
{
	engine->inputManager->RemoveListener(this);
}
