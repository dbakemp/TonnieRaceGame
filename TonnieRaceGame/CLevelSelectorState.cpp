#include "CLevelSelectorState.h"

void CLevelSelectorState::init(CEngine * engine)
{

	this->engine = engine;
}

void CLevelSelectorState::clean(CEngine * engine)
{
}

void CLevelSelectorState::pause()
{
}

void CLevelSelectorState::resume()
{
}

void CLevelSelectorState::handleEvents(CEngine * engine)
{
}

void CLevelSelectorState::update(CEngine * engine)
{
}

void CLevelSelectorState::draw(CEngine * engine)
{
}

void CLevelSelectorState::input(CEngine * engine, SDL_Event * event)
{
}

void CLevelSelectorState::checkSeque()
{
}

CLevelSelectorState::CLevelSelectorState(CEngine * engine)
{
}

void CLevelSelectorState::OnButtonClick(CUIButton * button)
{
	init(engine);
}
