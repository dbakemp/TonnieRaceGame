#include "SDL.h"
#include "CStateManager.h"
#include "CCamera.h"
#include "AdHelper.h"
#include "CPauseState.h"
#include "CDrawManager.h"
#include "CDeltaHelper.h"
#include "CInputManager.h"
#include  "CProfileManager.h"
#include "CEntityManager.h"
#include <curl/curl.h>
#include "CUILabel.h"
#include "CUIContainer.h"
#include "CUIImage.h"
#include "CUIButton.h"
#include "EUIAlignment.h"
#include "CPlayState.h"
#include "CTimerHelper.h"

void CPauseState::init(CEngine* engine)
{
	background = new CUIImage(engine, "Images/main.png");
	background->SetHorizontalAlignment(EUIALignmentHorizontal::CENTER);
	background->SetVerticalAlignment(EUIALignmentVertical::CENTER);
	background->SetVerticalStretch(EUIStretchVertical::FIT);
	background->ChangeZIndex(background->zIndex+3);

	tonnie = new CUIImage(engine, "Images/logo.png");
	tonnie->SetHorizontalAlignment(EUIALignmentHorizontal::CENTER);
	tonnie->SetVerticalAlignment(EUIALignmentVertical::CENTER);
	tonnie->SetPosition(0, -100);
	tonnie->ChangeZIndex(tonnie->zIndex + 3);

	label = new CUILabel(engine, "Bangers", "SPEL GEPAUZEERD");
	label->SetHorizontalAlignment(EUIALignmentHorizontal::CENTER);
	label->SetVerticalAlignment(EUIALignmentVertical::CENTER);
	label->SetFontSize(36);
	label->SetPosition(0, 200);
	label->SetVisibility(true);
	label->ChangeZIndex(label->zIndex + 3);

	buttonBack = new CUIButton(engine, "Bangers", "Stop", "Images/terug.png");
	buttonBack->SetHorizontalAlignment(EUIALignmentHorizontal::LEFT);
	buttonBack->SetVerticalAlignment(EUIALignmentVertical::BOTTOM);
	buttonBack->SetPosition(100, -50);
	buttonBack->SetFontSize(30);
	buttonBack->SetClickCallback(std::bind(&CPauseState::OnButtonClick, this, std::placeholders::_1));
	buttonBack->ChangeZIndex(buttonBack->zIndex + 3);
	buttonBack->GetLabel()->ChangeZIndex(buttonBack->GetLabel()->zIndex + 3);

	engine->timerHelper->Pause();

	this->engine = engine;
}

void CPauseState::clean(CEngine* engine)
{
	delete background;
	delete tonnie;
	delete label;
	delete buttonBack->GetLabel();
	delete buttonBack;

	engine->timerHelper->Resume();
}

void CPauseState::pause()
{
}

void CPauseState::resume()
{
}

void CPauseState::handleEvents(CEngine* engine)
{
}

void CPauseState::update(CEngine* engine)
{
	SDL_Delay((1000.0 / 60) - engine->deltaHelper->GetScaledDelta());
	checkSeque();
}

void CPauseState::draw(CEngine* engine)
{
	engine->drawManager->Tick(engine->renderer);
}

void CPauseState::input(CEngine* engine, SDL_Event* event)
{
	if (event->type == SDL_KEYDOWN)
	{
		switch (event->key.keysym.sym)
		{
		case SDLK_ESCAPE:
			engine->musicHelper->resumeMusic();
			stateSeque = EGameState::Resumed;
			shouldSeque = true;
			//engine->stateManager->changeState(Resumed, engine);
			break;
		}

	}

	engine->inputManager->Tick(event);
}

void CPauseState::checkSeque()
{
	if (!shouldSeque) { return; }

	engine->stateManager->changeState(stateSeque, engine);

}

CPauseState::CPauseState(CEngine* engine)
{
	init(engine);
}

void CPauseState::OnButtonClick(CUIButton* button)
{
	stateSeque = EGameState::Resumed;
	shouldSeque = true;
	engine->stateManager->playState->stateSeque = EGameState::Menu;
	engine->stateManager->playState->shouldSeque = true;
}
