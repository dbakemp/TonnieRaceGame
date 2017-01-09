#include "SDL.h"
#include "CStateManager.h"
#include "CCamera.h"
#include "CProfileCreationState.h"
#include "CDrawManager.h"
#include "CDeltaHelper.h"
#include "CInputManager.h"
#include "CEntityManager.h"
#include <curl/curl.h>
#include "CUILabel.h"
#include "CUIImage.h"
#include "CUIButton.h"
#include "EUIAlignment.h"
#include "CDebugLogger.h"

#include "CProfileManager.h"

void CProfileCreationState::init(CEngine* engine)
{
	CUIImage* background = new CUIImage(engine, "Images/main.png");
	background->SetHorizontalAlignment(EUIALignmentHorizontal::CENTER);
	background->SetVerticalAlignment(EUIALignmentVertical::CENTER);
	background->SetVerticalStretch(EUIStretchVertical::FIT);

	CUIImage* bord = new CUIImage(engine, "Images/scoreboard.png");
	bord->SetHorizontalAlignment(EUIALignmentHorizontal::CENTER);
	bord->SetVerticalAlignment(EUIALignmentVertical::CENTER);
	bord->SetPosition(0, -100);

	CUILabel* noProfile = new CUILabel(engine, "Bangers", "Voer hier je naam in : ");
	noProfile->SetHorizontalAlignment(EUIALignmentHorizontal::CENTER);
	noProfile->SetVerticalAlignment(EUIALignmentVertical::TOP);
	noProfile->SetPosition(0, 150);
	noProfile->SetFontSize(30);

	profileName = new CUILabel(engine, "Bangers", "TEST");
	profileName->SetHorizontalAlignment(EUIALignmentHorizontal::CENTER);
	profileName->SetVerticalAlignment(EUIALignmentVertical::TOP);
	profileName->SetPosition(0, 250);
	profileName->SetFontSize(30);
	
	CUIButton* buttonok = new CUIButton(engine, "Bangers", "Oké", "Images/groen.png");
	buttonok->SetHorizontalAlignment(EUIALignmentHorizontal::CENTER);
	buttonok->SetVerticalAlignment(EUIALignmentVertical::BOTTOM);
	buttonok->SetPosition(0, -50);
	buttonok->SetFontSize(30);
	buttonok->SetClickCallback(std::bind(&CProfileCreationState::OnButtonClick, this, std::placeholders::_1));

	this->engine = engine;

	SDL_StartTextInput();
}

void CProfileCreationState::clean(CEngine* engine)
{
	engine->entityManager->Clear();
}

void CProfileCreationState::pause()
{
}

void CProfileCreationState::resume()
{
}

void CProfileCreationState::handleEvents(CEngine* engine)
{
}

void CProfileCreationState::update(CEngine* engine)
{
	engine->entityManager->Tick();
	SDL_Delay((1000.0 / 60) - engine->deltaHelper->GetScaledDelta());

	profileName->SetText(currentName);

	
	checkSeque();
}

void CProfileCreationState::draw(CEngine* engine)
{
	engine->drawManager->Tick(engine->renderer);
}

void CProfileCreationState::input(CEngine* engine, SDL_Event* event)
{
	engine->inputManager->Tick(event);

	switch (event->type) {
	case SDL_TEXTINPUT:
		/* Add new text onto the end of our text */
		CDebugLogger::PrintDebug(event->text.text);
		currentName += event->text.text;
		break;
	case SDL_KEYDOWN:
		//Handle backspace
		if (event->key.keysym.sym == SDLK_BACKSPACE && currentName.length() > 0)
		{
			//lop off character
			currentName.pop_back();
		}

		break;
	}
}

void CProfileCreationState::checkSeque()
{
	if (engine->profileManager->existingProfile) shouldSeque = true;
	if (!shouldSeque) { return; }

	engine->stateManager->changeState(stateSeque, engine);
}

CProfileCreationState::CProfileCreationState(CEngine* engine)
{
	init(engine);
}

CProfileCreationState::~CProfileCreationState()
{
	delete background;
	background = nullptr;
}

void CProfileCreationState::OnButtonClick(CUIButton* button)
{
	if (button->GetText() == "Oké")
	{
		engine->profileManager->currentProfile = new CPlayerProfile();
		engine->profileManager->currentProfile->initializeNewProfile(currentName);
		engine->profileManager->saveProfile();

		shouldSeque = true;
		stateSeque = EGameState::Menu;
	}
}
