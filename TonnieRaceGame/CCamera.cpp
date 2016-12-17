#include "CCamera.h"
#include "CEntity.h"
#include "IDrawListener.h"
#include "CDeltaHelper.h"

CCamera::CCamera(CEngine* engine)
{
	posX = 0;
	posY = 0;
	child = nullptr;
	viewport = { 0, 0, engine->windowWidth, engine->windowHeight };
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
		posX = (((aabb.lowerBound.x * 5) - ((viewport.w - ((aabb.upperBound.x - aabb.lowerBound.x) * 5)) / 2))) - viewport.x;
		posY = (((aabb.lowerBound.y * 5) - ((viewport.h - ((aabb.upperBound.y - aabb.lowerBound.y) * 5)) / 2))) - viewport.y;
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

void CCamera::SetViewPort(int w, int h, int x, int y)
{
	viewport = { x, y, w, h };
}

SDL_Rect CCamera::GetViewPort()
{
	return viewport;
}
