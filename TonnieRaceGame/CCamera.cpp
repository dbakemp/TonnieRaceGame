#include "CCamera.h"
#include "CEntity.h"
#include "IDrawListener.h"

CCamera::CCamera()
{
	posX = -500;
	posY = -500;
	windowHeight = 720;
	windowWidth = 1280;
	child = nullptr;
}

void CCamera::Update()
{
	b2AABB aabb;
	aabb.lowerBound = b2Vec2(FLT_MAX, FLT_MAX);
	aabb.upperBound = b2Vec2(-FLT_MAX, -FLT_MAX);
	b2Fixture* fixture = child->body->GetFixtureList();
	while (fixture != NULL)
	{
		aabb.Combine(aabb, fixture->GetAABB(0));
		fixture = fixture->GetNext();
	}


	if (child != nullptr)
	{
		posX += (((aabb.lowerBound.x * 5) - ((windowWidth - ((aabb.upperBound.x - aabb.lowerBound.x) * 5)) / 2) - posX) / 8);
		posY += (((aabb.lowerBound.y * 5) - ((windowHeight - ((aabb.upperBound.y - aabb.lowerBound.y) * 5)) / 2) - posY) / 8);
	}
}

void CCamera::SetChild(IBox2DListener* child)
{
	this->child = child;
}

IBox2DListener* CCamera::GetChild()
{
	return child;
}