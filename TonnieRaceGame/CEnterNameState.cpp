#include "SDL.h"
#include "CStateManager.h"
#include "CCamera.h"
#include "CEnterNameState.h"
#include "CDrawManager.h"
#include "CInputManager.h"
#include "CDeltaHelper.h"
#include "CEntityManager.h"
#include "CUIImage.h"
#include "CUIButton.h"
#include "EUIAlignment.h"
#include "HighscoresHelper.h"
#include "CDebugLogger.h"
#include <functional>

void CEnterNameState::init(CEngine* engine)
{
	P1Name = "_";
	P2Name = "_";
	CUIImage* background = new CUIImage(engine, "Images/main.png");
	background->SetHorizontalAlignment(EUIALignmentHorizontal::CENTER);
	background->SetVerticalAlignment(EUIALignmentVertical::CENTER);
	background->SetVerticalStretch(EUIStretchVertical::FIT);
	
	CUIImage* tonnie = new CUIImage(engine, "Images/logo.png");
	tonnie->SetHorizontalAlignment(EUIALignmentHorizontal::CENTER);
	tonnie->SetVerticalAlignment(EUIALignmentVertical::CENTER);
	tonnie->SetPosition(0, -100);

	CUILabel* label = new CUILabel(engine, "Bangers", "Speler 1, vul uw naam in:");
	label->SetFontSize(30);
	label->SetHorizontalAlignment(EUIALignmentHorizontal::CENTER);
	label->SetVerticalAlignment(EUIALignmentVertical::TOP);
	label->SetPosition(0, 500);

	nameLabel = new CUILabel(engine, "Bangers", "_");
	nameLabel->SetFontSize(30);
	nameLabel->SetHorizontalAlignment(EUIALignmentHorizontal::CENTER);
	nameLabel->SetVerticalAlignment(EUIALignmentVertical::TOP);
	nameLabel->SetPosition(0, 550);


	HighscoresHelper* highScorersHelper = new HighscoresHelper();

	highScorersHelper->addHighScore("Tim", "00:14:00", 1);
	CDebugLogger::PrintDebug("Toegevoegd aan scoretjeeeeee");
	/*CUIButton* labeld = new CUIButton(engine, "Bangers", "Score uploaden", "Images/geel.png");
	labeld->SetHorizontalAlignment(EUIALignmentHorizontal::CENTER);
	labeld->SetVerticalAlignment(EUIALignmentVertical::BOTTOM);
	labeld->SetPosition(0,-30);
	labeld->SetFontSize(18);
	labeld->SetClickCallback(std::bind(&CEnterNameState::OnButtonClick, this, std::placeholders::_1));
*/

	this->engine = engine;
}

void CEnterNameState::clean(CEngine* engine)
{
	engine->entityManager->Clear();
}

void CEnterNameState::pause()
{
}

void CEnterNameState::resume()
{
}

void CEnterNameState::handleEvents(CEngine* engine)
{
}

void CEnterNameState::update(CEngine* engine)
{
	engine->entityManager->Tick();
	SDL_Delay((1000.0 / 60) - engine->deltaHelper->GetScaledDelta());
	checkSeque();

	nameLabel->SetText(P1Name);
}

void CEnterNameState::draw(CEngine* engine)
{
	engine->drawManager->Tick(engine->renderer);
}

void CEnterNameState::input(CEngine* engine, SDL_Event* event)
{
	if (event->type == SDL_KEYDOWN)
	{
		if (event->key.keysym.sym == SDLK_BACKSPACE)
		{
			P1Name = P1Name.substr(0, P1Name.size() - 1);

			if (P1Name.size() == 0)
			{
				P1Name = "_";
			}
		}
		else
		{
			if (P1Name == "_")
			{
				P1Name = "";
			}
			P1Name += event->key.keysym.sym;
		}

		
	}
	//engine->inputManager->Tick(event);
}

void CEnterNameState::checkSeque()
{
	if (!shouldSeque) { return; }

	engine->stateManager->changeState(stateSeque, engine);
}

void CEnterNameState::OnButtonClick(CUIButton* button)
{
	CDebugLogger::PrintDebug("AIDSSDFSF");
	//Naar highscores knallen


}

CEnterNameState::CEnterNameState(CEngine* engine)
{
	init(engine);
}

CEnterNameState::~CEnterNameState()
{
}
