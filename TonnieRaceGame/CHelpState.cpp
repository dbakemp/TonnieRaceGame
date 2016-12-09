#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "CStateManager.h"
#include "CCamera.h"
#include "CHelpState.h"
#include "CDrawManager.h"
#include "CDeltaHelper.h"
#include "CInputManager.h"
#include "CEntityManager.h"
#include "CBox2DManager.h"
#include <iostream>
#include <curl/curl.h>
#include "CUILabel.h"
#include "CUIImage.h"
#include "CUIButton.h"
#include "EUIAlignment.h"

void CHelpState::init(CEngine* engine)
{
	CUIImage* background = new CUIImage(engine, "Resources/Images/main.png");
	background->SetHorizontalAlignment(EUIALignmentHorizontal::CENTER);
	background->SetVerticalAlignment(EUIALignmentVertical::CENTER);
	background->SetVerticalStretch(EUIStretchVertical::FIT);

	CUIImage* tonnie = new CUIImage(engine, "Resources/Images/logo.png");
	tonnie->SetHorizontalAlignment(EUIALignmentHorizontal::CENTER);
	tonnie->SetVerticalAlignment(EUIALignmentVertical::CENTER);
	tonnie->SetPosition(0, -100);

	CUIButton* buttonBack = new CUIButton(engine, "Bangers", "Terug", "Resources/Images/terug.png");
	buttonBack->SetHorizontalAlignment(EUIALignmentHorizontal::LEFT);
	buttonBack->SetVerticalAlignment(EUIALignmentVertical::BOTTOM);
	buttonBack->SetPosition(100, -50);
	buttonBack->SetFontSize(30);
	buttonBack->SetClickCallback(std::bind(&CHelpState::OnButtonClick, this, std::placeholders::_1));

	CUILabel* label = new CUILabel(engine, "Bangers", "Hier komt de help!");
	label->SetHorizontalAlignment(EUIALignmentHorizontal::CENTER);
	label->SetVerticalAlignment(EUIALignmentVertical::BOTTOM);
	label->SetPosition(0, -200);
	label->SetFontSize(50);

	engine->musicHelper->playTrack("Resources/Music/plingplongplong.mp3", false);

	this->engine = engine;
	
}

void CHelpState::clean(CEngine* engine)
{
	engine->drawManager->Clear();
	engine->inputManager->Clear();
	engine->box2DManager->Clear();
	engine->entityManager->Clear();
}

void CHelpState::pause()
{
}

void CHelpState::resume()
{
}

void CHelpState::handleEvents(CEngine* engine)
{
}

void CHelpState::update(CEngine* engine)
{
	engine->entityManager->Tick();
	SDL_Delay((1000.0 / 60) - engine->deltaHelper->delta);
	checkSeque();
}

void CHelpState::draw(CEngine* engine)
{
	engine->drawManager->Tick(engine->renderer);
}

void CHelpState::input(CEngine* engine, SDL_Event * event)
{
	engine->inputManager->Tick(event);
}

void CHelpState::checkSeque()
{
	if (!shouldSeque) { return; }

	engine->stateManager->changeState(stateSeque, engine);
}

CHelpState::CHelpState(CEngine* engine)
{
	init(engine);
}

void CHelpState::OnButtonClick(CUIButton* button)
{
	if (button->GetText() == "Terug") {
		shouldSeque = true;
		stateSeque = EGameState::Menu;
	}
}
