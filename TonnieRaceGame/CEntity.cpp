#include "CEntity.h"
#include "CEngine.h"

CEntity::CEntity(CEngine* engine): IEntityListener(engine)
{
}

CEntity::~CEntity()
{
}

void CEntity::Update()
{
}

void CEntity::CollisionBegin(CEntity* collider)
{
}

void CEntity::CollisionEnd(CEntity* collider)
{
}

void CEntity::SetType(Type type)
{
	this->type = type;
}

CEntity::Type CEntity::GetType()
{
	return type;
}
