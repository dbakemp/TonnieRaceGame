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

	CUIImage* r1 = new CUIImage(engine, "Images/r1.png");
	r1->SetHorizontalAlignment(EUIALignmentHorizontal::CENTER);
	r1->SetVerticalAlignment(EUIALignmentVertical::CENTER);
	r1->SetPosition(270, -50);

	CUIImage* rb = new CUIImage(engine, "Images/rb.png");
	rb->SetHorizontalAlignment(EUIALignmentHorizontal::CENTER);
	rb->SetVerticalAlignment(EUIALignmentVertical::CENTER);
	rb->SetPosition(220, -50);

	CUIImage* l1 = new CUIImage(engine, "Images/l1.png");
	l1->SetHorizontalAlignment(EUIALignmentHorizontal::CENTER);
	l1->SetVerticalAlignment(EUIALignmentVertical::CENTER);
	l1->SetPosition(270, -23);

	CUIImage* lb = new CUIImage(engine, "Images/lb.png");
	lb->SetHorizontalAlignment(EUIALignmentHorizontal::CENTER);
	lb->SetVerticalAlignment(EUIALignmentVertical::CENTER);
	lb->SetPosition(220, -23);

	CUIImage* vierkantje = new CUIImage(engine, "Images/vierkantje.png");
	vierkantje->SetHorizontalAlignment(EUIALignmentHorizontal::CENTER);
	vierkantje->SetVerticalAlignment(EUIALignmentVertical::CENTER);
	vierkantje->SetPosition(270, 10);

	CUIImage* x = new CUIImage(engine, "Images/x.png");
	x->SetHorizontalAlignment(EUIALignmentHorizontal::CENTER);
	x->SetVerticalAlignment(EUIALignmentVertical::CENTER);
	x->SetPosition(220, 10);

	CUIImage* kruiske = new CUIImage(engine, "Images/kruiske.png");
	kruiske->SetHorizontalAlignment(EUIALignmentHorizontal::CENTER);
	kruiske->SetVerticalAlignment(EUIALignmentVertical::CENTER);
	kruiske->SetPosition(270, 45);

	CUIImage* aaaaatje = new CUIImage(engine, "Images/aaaaatje.png");
	aaaaatje->SetHorizontalAlignment(EUIALignmentHorizontal::CENTER);
	aaaaatje->SetVerticalAlignment(EUIALignmentVertical::CENTER);
	aaaaatje->SetPosition(220, 45);

	CUIImage* toetsie = new CUIImage(engine, "Images/toetsenbord.png");
	toetsie->SetHorizontalAlignment(EUIALignmentHorizontal::CENTER);
	toetsie->SetVerticalAlignment(EUIALignmentVertical::CENTER);
	toetsie->SetPosition(0, 0);

	CUILabel* labelToetsie = new CUILabel(engine, "Bangers", "Auto besturen");
	labelToetsie->SetFontSize(20);
	labelToetsie->SetHorizontalAlignment(EUIALignmentHorizontal::LEFT);
	labelToetsie->SetVerticalAlignment(EUIALignmentVertical::TOP);
	labelToetsie->SetPosition(100, 190);

	CUIImage* spacebarrie = new CUIImage(engine, "Images/spacebarrie.png");
	spacebarrie->SetHorizontalAlignment(EUIALignmentHorizontal::CENTER);
	spacebarrie->SetVerticalAlignment(EUIALignmentVertical::CENTER);
	spacebarrie->SetPosition(0, 110);

	CUILabel* labelSpace = new CUILabel(engine, "Bangers", "Powerup uitvoeren");
	labelSpace->SetFontSize(20);
	labelSpace->SetHorizontalAlignment(EUIALignmentHorizontal::LEFT);
	labelSpace->SetVerticalAlignment(EUIALignmentVertical::TOP);
	labelSpace->SetPosition(78, 260);

	CUIImage* shieft = new CUIImage(engine, "Images/shieft.png");
	shieft->SetHorizontalAlignment(EUIALignmentHorizontal::CENTER);
	shieft->SetVerticalAlignment(EUIALignmentVertical::CENTER);
	shieft->SetPosition(0, 185);

	CUILabel* labelShieft = new CUILabel(engine, "Bangers", "Toeteren");
	labelShieft->SetFontSize(20);
	labelShieft->SetHorizontalAlignment(EUIALignmentHorizontal::LEFT);
	labelShieft->SetVerticalAlignment(EUIALignmentVertical::TOP);
	labelShieft->SetPosition(115, 342);

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
	labelrrb->SetPosition(10, 0 + labelrra->GetRectangle().y + labelrra->GetRectangle().h + 10);

	CUILabel* labelrrc = new CUILabel(engine, "Bangers", "Toeteren");
	labelrrc->SetFontSize(20);
	labelrrc->SetHorizontalAlignment(EUIALignmentHorizontal::LEFT);
	labelrrc->SetVerticalAlignment(EUIALignmentVertical::TOP);
	labelrrc->SetPosition(10, 0 + labelrrb->GetRectangle().y + labelrrb->GetRectangle().h + 10);

	CUILabel* labelrrd = new CUILabel(engine, "Bangers", "Power-Up");
	labelrrd->SetFontSize(20);
	labelrrd->SetHorizontalAlignment(EUIALignmentHorizontal::LEFT);
	labelrrd->SetVerticalAlignment(EUIALignmentVertical::TOP);
	labelrrd->SetPosition(10, 0 + labelrrc->GetRectangle().y + labelrrc->GetRectangle().h + 10);

	CUIContainer* containerlc = new CUIContainer(engine);
	containerlc->SetHorizontalAlignment(EUIALignmentHorizontal::CENTER);
	containerlc->SetVerticalAlignment(EUIALignmentVertical::BOTTOM);
	containerlc->SetHeight(300 - labelr->GetRectangle().h - 5);
	containerlc->SetWidth(300);
	containerlc->AddUIElement(labell);
	containerlc->AddUIElement(toetsie);
	containerlc->AddUIElement(labelToetsie);
	containerlc->AddUIElement(spacebarrie);
	containerlc->AddUIElement(labelSpace);
	containerlc->AddUIElement(shieft);
	containerlc->AddUIElement(labelShieft);

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
	containerrr->AddUIElement(labelrrd);

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
