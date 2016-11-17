#include "SDL.h"
#include "CStateManager.h"
#include "CPlayState.h"
#include "CEngine.h"
#include "CEntityCar.h"
#include "CEntitySmallSquare.h"

void CPlayState::init()
{
	return;
}

void CPlayState::init(CEngine* engine)
{
	b2Vec2 gravity(0, 0);

	engine->world = new b2World(gravity);

	camera = new CCamera();
	camera->windowHeight = 720;
	camera->windowWidth = 1280;

	engine->camera = camera;

	CEntityCar* car = new CEntityCar(engine);
	camera->SetChild(car);

	for (int i = 0; i < 200; i++) {
		new CEntitySmallSquare(engine);
	}
}

void CPlayState::clean()
{
}

void CPlayState::pause()
{
}

void CPlayState::resume()
{
}

void CPlayState::handleEvents(CEngine * engine)
{
}

void CPlayState::update(CEngine * engine)
{

}

void CPlayState::draw(CEngine * engine)
{
}

CPlayState::CPlayState(CEngine * engine)
{
	init(engine);
}

CPlayState::~CPlayState()
{
	clean();
}
