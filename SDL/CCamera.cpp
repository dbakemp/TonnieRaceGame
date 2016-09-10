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
	posX += ((child->xPos - ((1920-child->width)/2) - posX) / 8);
	posY += ((child->yPos - ((1080-child->height)/2) - posY) / 8);
}

void CCamera::SetChild(CEntity * child)
{
	this->child = child;
}

CEntity *CCamera::GetChild()
{
	return child;
}
