#include "SDL.h"
#include "CStateManager.h"
#include "CCamera.h"
#include "AdHelper.h"
#include "CLoadingState.h"
#include "CDrawManager.h"
#include "CDeltaHelper.h"
#include "CInputManager.h"
#include "CEntityManager.h"
#include <curl/curl.h>
#include "CUILabel.h"
#include "CUIContainer.h"
#include "CUIImage.h"
#include "CUIButton.h"
#include "EUIAlignment.h"

void CLoadingState::init(CEngine* engine)
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
	label = new CUILabel(engine, "Bangers", "Aan het laden...");
	label->SetHorizontalAlignment(EUIALignmentHorizontal::CENTER);
	label->SetVerticalAlignment(EUIALignmentVertical::CENTER);
	label->SetFontSize(36);
	label->SetPosition(0, 200);
	label->SetVisibility(true);
	this->engine = engine;
}

void CLoadingState::clean(CEngine* engine)
{
	engine->entityManager->Clear();
	engine->adHelper = new AdHelper();
}

void CLoadingState::pause()
{
}

void CLoadingState::resume()
{
}

void CLoadingState::handleEvents(CEngine* engine)
{
}

void CLoadingState::update(CEngine* engine)
{
	engine->entityManager->Tick();
	SDL_Delay((1000.0 / 60) - engine->deltaHelper->GetScaledDelta());
	checkSeque();
}

void CLoadingState::draw(CEngine* engine)
{
	engine->drawManager->Tick(engine->renderer);
	stateSeque = Menu;
	shouldSeque = 1;
}

void CLoadingState::input(CEngine* engine, SDL_Event* event)
{
	engine->inputManager->Tick(event);
}

void CLoadingState::checkSeque()
{
	if (!shouldSeque) { return; }

	engine->stateManager->changeState(stateSeque, engine);
}

CLoadingState::CLoadingState(CEngine* engine)
{
	init(engine);
}

void CLoadingState::OnButtonClick(CUIButton* button)
{
	if (button->GetText() == "Terug")
	{
		shouldSeque = true;
		stateSeque = EGameState::Menu;
	}
}
