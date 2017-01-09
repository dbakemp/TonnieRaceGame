#include "SDL.h"
#include "CStateManager.h"
#include "CCamera.h"
#include "CHelpState.h"
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

void CHelpState::init(CEngine* engine)
{
	CUIImage* background = new CUIImage(engine, "Images/main.png");
	background->SetHorizontalAlignment(EUIALignmentHorizontal::CENTER);
	background->SetVerticalAlignment(EUIALignmentVertical::CENTER);
	background->SetVerticalStretch(EUIStretchVertical::FIT);

	CUIButton* buttonBack = new CUIButton(engine, "Bangers", "Terug", "Images/terug.png");
	buttonBack->SetHorizontalAlignment(EUIALignmentHorizontal::LEFT);
	buttonBack->SetVerticalAlignment(EUIALignmentVertical::BOTTOM);
	buttonBack->SetPosition(100, -50);
	buttonBack->SetFontSize(30);
	buttonBack->SetClickCallback(std::bind(&CHelpState::OnButtonClick, this, std::placeholders::_1));

	CUILabel* labell = new CUILabel(engine, "Bangers", "Toetsenbord Besturing");
	labell->SetFontSize(30);
	labell->SetHorizontalAlignment(EUIALignmentHorizontal::CENTER);
	labell->SetVerticalAlignment(EUIALignmentVertical::TOP);

	CUILabel* labelr = new CUILabel(engine, "Bangers", "Controller Besturing");
	labelr->SetFontSize(30);
	labelr->SetHorizontalAlignment(EUIALignmentHorizontal::CENTER);
	labelr->SetVerticalAlignment(EUIALignmentVertical::TOP);

	CUILabel* labelrra = new CUILabel(engine, "Bangers", "Gas Geven");
	labelrra->SetFontSize(20);
	labelrra->SetHorizontalAlignment(EUIALignmentHorizontal::LEFT);
	labelrra->SetVerticalAlignment(EUIALignmentVertical::TOP);
	labelrra->SetPosition(10, 0);

	CUILabel* labelrrb = new CUILabel(engine, "Bangers", "Remmen");
	labelrrb->SetFontSize(20);
	labelrrb->SetHorizontalAlignment(EUIALignmentHorizontal::LEFT);
	labelrrb->SetVerticalAlignment(EUIALignmentVertical::TOP);
	labelrrb->SetPosition(10, 0 + labelrra->GetRectangle().y + labelrra->GetRectangle().h + 5);

	CUILabel* labelrrc = new CUILabel(engine, "Bangers", "Toeteren");
	labelrrc->SetFontSize(20);
	labelrrc->SetHorizontalAlignment(EUIALignmentHorizontal::LEFT);
	labelrrc->SetVerticalAlignment(EUIALignmentVertical::TOP);
	labelrrc->SetPosition(10, 0 + labelrrb->GetRectangle().y + labelrrb->GetRectangle().h + 5);

	CUIContainer* containerlc = new CUIContainer(engine);
	containerlc->SetHorizontalAlignment(EUIALignmentHorizontal::CENTER);
	containerlc->SetVerticalAlignment(EUIALignmentVertical::BOTTOM);
	containerlc->SetHeight(200 - labelr->GetRectangle().h - 5);
	containerlc->SetWidth(300);

	CUIContainer* containerrl = new CUIContainer(engine);
	containerrl->SetHorizontalAlignment(EUIALignmentHorizontal::LEFT);
	containerrl->SetVerticalAlignment(EUIALignmentVertical::BOTTOM);
	containerrl->SetHeight(200 - labelr->GetRectangle().h - 5);
	containerrl->SetWidth(150);

	CUIContainer* containerrr = new CUIContainer(engine);
	containerrr->SetHorizontalAlignment(EUIALignmentHorizontal::RIGHT);
	containerrr->SetVerticalAlignment(EUIALignmentVertical::BOTTOM);
	containerrr->SetHeight(200 - labelr->GetRectangle().h - 5);
	containerrr->SetWidth(150);
	containerrr->AddUIElement(labelrra);
	containerrr->AddUIElement(labelrrb);
	containerrr->AddUIElement(labelrrc);

	CUIContainer* containerl = new CUIContainer(engine);
	containerl->SetHorizontalAlignment(EUIALignmentHorizontal::CENTER);
	containerl->SetVerticalAlignment(EUIALignmentVertical::CENTER);
	containerl->SetHeight(200);
	containerl->SetWidth(300);
	containerl->SetPosition(-300, 0);
	containerl->AddUIElement(labell);
	containerl->AddUIElement(containerlc);

	CUIContainer* containerr = new CUIContainer(engine);
	containerr->SetHorizontalAlignment(EUIALignmentHorizontal::CENTER);
	containerr->SetVerticalAlignment(EUIALignmentVertical::CENTER);
	containerr->SetHeight(200);
	containerr->SetWidth(300);
	containerr->SetPosition(300, 0);
	containerr->AddUIElement(labelr);
	containerr->AddUIElement(containerrr);
	containerr->AddUIElement(containerrl);

	this->engine = engine;
}

void CHelpState::clean(CEngine* engine)
{
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
	SDL_Delay((1000.0 / 60) - engine->deltaHelper->GetScaledDelta());
	checkSeque();
}

void CHelpState::draw(CEngine* engine)
{
	engine->drawManager->Tick(engine->renderer);
}

void CHelpState::input(CEngine* engine, SDL_Event* event)
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
	if (button->GetText() == "Terug")
	{
		shouldSeque = true;
		stateSeque = EGameState::Menu;
	}
}
