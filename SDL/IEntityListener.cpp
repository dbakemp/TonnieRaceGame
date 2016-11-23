#include "IEntityListener.h"
#include "CEntityManager.h"
#include "CEngine.h"

IEntityListener::IEntityListener(CEngine* engine)
{
	this->engine = engine;
	engine->entityManager->AddListener(this);
}

IEntityListener::~IEntityListener()
{
	engine->entityManager->RemoveListener(this);
}
