#include "SDL.h"
#include "CStateManager.h"
#include "CCamera.h"
#include "CIntroState.h"
#include "CDrawManager.h"
#include "CInputManager.h"
#include "CDeltaHelper.h"
#include "CEntityManager.h"
#include "CUIImage.h"
#include "CUIButton.h"
#include "EUIAlignment.h"
#include <functional>

void CIntroState::init(CEngine* engine)
{
	CUIImage* background = new CUIImage(engine, "Images/main.png");
	background->SetHorizontalAlignment(EUIALignmentHorizontal::CENTER);
	background->SetVerticalAlignment(EUIALignmentVertical::CENTER);
	background->SetVerticalStretch(EUIStretchVertical::FIT);

	CUIImage* tonnie = new CUIImage(engine, "Images/logo.png");
	tonnie->SetHorizontalAlignment(EUIALignmentHorizontal::CENTER);
	tonnie->SetVerticalAlignment(EUIALignmentVertical::CENTER);
	tonnie->SetPosition(0, -100);

	CUIButton* labela = new CUIButton(engine, "Bangers", "Spelen", "Images/blauw.png");
	labela->SetHorizontalAlignment(EUIALignmentHorizontal::CENTER);
	labela->SetVerticalAlignment(EUIALignmentVertical::BOTTOM);
	labela->SetPosition(-300, -100);
	labela->SetFontSize(30);
	labela->SetClickCallback(std::bind(&CIntroState::OnButtonClick, this, std::placeholders::_1));

	CUIButton* labelb = new CUIButton(engine, "Bangers", "Help", "Images/rood.png");
	labelb->SetHorizontalAlignment(EUIALignmentHorizontal::CENTER);
	labelb->SetVerticalAlignment(EUIALignmentVertical::BOTTOM);
	labelb->SetPosition(-100, -100);
	labelb->SetFontSize(30);
	labelb->SetClickCallback(std::bind(&CIntroState::OnButtonClick, this, std::placeholders::_1));

	CUIButton* labelc = new CUIButton(engine, "Bangers", "Scores", "Images/groen.png");
	labelc->SetHorizontalAlignment(EUIALignmentHorizontal::CENTER);
	labelc->SetVerticalAlignment(EUIALignmentVertical::BOTTOM);
	labelc->SetPosition(100, -100);
	labelc->SetFontSize(30);
	labelc->SetClickCallback(std::bind(&CIntroState::OnButtonClick, this, std::placeholders::_1));

	CUIButton* labeld = new CUIButton(engine, "Bangers", "Credits", "Images/geel.png");
	labeld->SetHorizontalAlignment(EUIALignmentHorizontal::CENTER);
	labeld->SetVerticalAlignment(EUIALignmentVertical::BOTTOM);
	labeld->SetPosition(300, -100);
	labeld->SetFontSize(30);
	labeld->SetClickCallback(std::bind(&CIntroState::OnButtonClick, this, std::placeholders::_1));

	this->engine = engine;
}

void CIntroState::clean(CEngine* engine)
{
	engine->entityManager->Clear();
}

void CIntroState::pause()
{
}

void CIntroState::resume()
{
}

void CIntroState::handleEvents(CEngine* engine)
{
}

void CIntroState::update(CEngine* engine)
{
	engine->entityManager->Tick();
	SDL_Delay((1000.0 / 60) - engine->deltaHelper->GetScaledDelta());
	checkSeque();
}

void CIntroState::draw(CEngine* engine)
{
	engine->drawManager->Tick(engine->renderer);
}

void CIntroState::input(CEngine* engine, SDL_Event* event)
{
	engine->inputManager->Tick(event);
}

void CIntroState::checkSeque()
{
	if (!shouldSeque) { return; }

	engine->stateManager->changeState(stateSeque, engine);
}

void CIntroState::OnButtonClick(CUIButton* button)
{
	if (button->GetText() == "Spelen")
	{
		shouldSeque = true;
		stateSeque = EGameState::LevelSelector;
	}
	else if (button->GetText() == "Help")
	{
		shouldSeque = true;
		stateSeque = EGameState::Help;
	}
	else if (button->GetText() == "Scores")
	{
		shouldSeque = true;
		stateSeque = EGameState::Scores;
	}
	else if (button->GetText() == "Credits")
	{
		shouldSeque = true;
		stateSeque = EGameState::Credits;
	}
}

CIntroState::CIntroState(CEngine* engine)
{
	init(engine);
}

CIntroState::~CIntroState()
{
}
