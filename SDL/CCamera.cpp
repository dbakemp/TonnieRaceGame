#include "CCamera.h"
#include "CEntity.h"
#include "IDrawListener.h"

CCamera::CCamera()
{
	posX = 0;
	posY = 0;
}

void CCamera::Update()
{
	posX += ((child->xPos - ((800-child->width)/2) - posX) / 16);
	posY += ((child->yPos - ((600-child->height)/2) - posY) / 16);
}

void CCamera::SetChild(CEntity * child)
{
	this->child = child;
}

CEntity *CCamera::GetChild()
{
	return child;
}
