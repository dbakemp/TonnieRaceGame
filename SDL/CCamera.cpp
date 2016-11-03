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
	if (child != nullptr) {
		posX += ((child->xPos - ((windowWidth - child->width) / 2) - posX) / 8);
		posY += ((child->yPos - ((windowHeight - child->height) / 2) - posY) / 8);
	}
}

void CCamera::SetChild(CEntity * child)
{
	this->child = child;
}

CEntity *CCamera::GetChild()
{
	return child;
}
