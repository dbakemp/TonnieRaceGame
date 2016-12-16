#include "CCollisionHelper.h"
#include "CEntity.h"
#include "CEntityCheckpoint.h"

void CCollisionHelper::BeginContact(b2Contact* contact)
{
	CEntity* entityA = static_cast<CEntity*>(contact->GetFixtureA()->GetBody()->GetUserData());
	CEntity* entityB = static_cast<CEntity*>(contact->GetFixtureB()->GetBody()->GetUserData());
	if (entityA != nullptr && entityB != nullptr)
	{
		entityA->CollisionBegin(entityB);
		entityB->CollisionBegin(entityA);
	}
}

void CCollisionHelper::EndContact(b2Contact* contact)
{
}
