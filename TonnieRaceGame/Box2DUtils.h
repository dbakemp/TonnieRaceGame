#ifndef BOX2DUTILS_H
#define BOX2DUTILS_H

#include <SDL.h>
#include <Box2D\Box2D.h>
#include "CCamera.h"

class Box2DUtils
{
public:
	static void Box2DUtils::DrawBody(SDL_Renderer* buffer, b2Body* body, CCamera* camera, int fr, int fg, int fb, int falpha, int lr, int lg, int lb, int lalpha, bool aa);
};

#endif
