#ifndef CENTITYBUILD_H
#define CENTITYBUILD_H

#include "IDrawListener.h"
#include "IInputListener.h"
#include "CEntity.h"
#include "CEngine.h"
#include "SDL_ttf.h"

class CEntityBuild : public CEntity, public IDrawListener, public IInputListener
{
public:
	CEntityBuild(CEngine* engine, TTF_Font* font);
	~CEntityBuild();
	void Update();
	void Draw(SDL_Renderer* renderer);
	void Input(SDL_Event* event);
private:
	CEngine* engine;
};

#endif
