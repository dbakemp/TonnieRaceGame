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

void CPauseState::init(CEngine* engine)
{
	CUIImage* background = new CUIImage(engine, "Images/main.png");
	background->SetHorizontalAlignment(EUIALignmentHorizontal::CENTER);
	background->SetVerticalAlignment(EUIALignmentVertical::CENTER);
	background->SetVerticalStretch(EUIStretchVertical::FIT);

	CUIImage* tonnie = new CUIImage(engine, "Images/logo.png");
	tonnie->SetHorizontalAlignment(EUIALignmentHorizontal::CENTER);
	tonnie->SetVerticalAlignment(EUIALignmentVertical::CENTER);
	tonnie->SetPosition(0, -100);

	CUILabel *label = new CUILabel(engine);
	label = new CUILabel(engine, "Bangers", "SPEL GEPAUZEERD");
	label->SetHorizontalAlignment(EUIALignmentHorizontal::CENTER);
	label->SetVerticalAlignment(EUIALignmentVertical::CENTER);
	label->SetFontSize(36);
	label->SetPosition(0, 200);
	label->SetVisibility(true);
	this->engine = engine;
}

void CPauseState::clean(CEngine* engine)
{
	engine->entityManager->Clear();
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
	engine->entityManager->Tick();
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
			//stateSeque = EGameState::Menu;
			//shouldSeque = true;
			engine->stateManager->changeState(Resumed, engine);
			break;
		}

	}

	engine->inputManager->Tick(event);
}

void CPauseState::checkSeque()
{
	if (!shouldSeque) { return; }

	if (engine->profileManager->existingProfile) {
		engine->stateManager->changeState(stateSeque, engine);
	}
	else {
		engine->stateManager->changeState(ProfileCreation, engine);
	}

}

CPauseState::CPauseState(CEngine* engine)
{
	init(engine);
}

void CPauseState::OnButtonClick(CUIButton* button)
{
	if (button->GetText() == "Terug")
	{
		shouldSeque = true;
		stateSeque = EGameState::Menu;
	}
}
