#include "CCamera.h"
#include "CEntity.h"
#include "IDrawListener.h"
#include "CDeltaHelper.h"

CCamera::CCamera(CEngine* engine)
{
	posX = -500;
	posY = -500;
	child = nullptr;
	this->engine = engine;
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
		posX += (((aabb.lowerBound.x * 5) - ((engine->windowWidth - ((aabb.upperBound.x - aabb.lowerBound.x) * 5)) / 2) - posX));
		posY += (((aabb.lowerBound.y * 5) - ((engine->windowHeight - ((aabb.upperBound.y - aabb.lowerBound.y) * 5)) / 2) - posY));
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

int CCamera::GetXPos()
{
	return posX;
}

int CCamera::GetYPos()
{
	return posY;
}
