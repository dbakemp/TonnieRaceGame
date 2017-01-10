#include "SDL.h"
#include "CStateManager.h"
#include "CCamera.h"
#include "CScoresState.h"
#include "CDrawManager.h"
#include "CDeltaHelper.h"
#include "CInputManager.h"
#include "CEntityManager.h"
#include <curl/curl.h>
#include "CUILabel.h"
#include "CUIImage.h"
#include "HighscoresHelper.h"
#include "CUIButton.h"
#include "EUIAlignment.h"

void CScoresState::init(CEngine* engine)
{
	HighscoresHelper* highscoreHelper = new HighscoresHelper();
	highscoreHelper->getHighscore(1);
	
	labels = highscoreHelper->processJSON();

	CUIImage* background = new CUIImage(engine, "Images/main.png");
	background->SetHorizontalAlignment(EUIALignmentHorizontal::CENTER);
	background->SetVerticalAlignment(EUIALignmentVertical::CENTER);
	background->SetVerticalStretch(EUIStretchVertical::FIT);

	CUIImage* tonnie = new CUIImage(engine, "Images/scoreboard.png");
	tonnie->SetHorizontalAlignment(EUIALignmentHorizontal::CENTER);
	tonnie->SetVerticalAlignment(EUIALignmentVertical::CENTER);
	tonnie->SetPosition(0, -100);

	CUIButton* buttonBack = new CUIButton(engine, "Bangers", "Terug", "Images/terug.png");
	buttonBack->SetHorizontalAlignment(EUIALignmentHorizontal::LEFT);
	buttonBack->SetVerticalAlignment(EUIALignmentVertical::BOTTOM);
	buttonBack->SetPosition(100, -50);
	buttonBack->SetFontSize(30);
	buttonBack->SetClickCallback(std::bind(&CScoresState::OnButtonClick, this, std::placeholders::_1));

	CUILabel* label = new CUILabel(engine, "Bangers", "Dit zijn de beste scores van Tonnie's grote racewereld!");
	label->SetHorizontalAlignment(EUIALignmentHorizontal::CENTER);
	label->SetVerticalAlignment(EUIALignmentVertical::BOTTOM);
	label->SetPosition(0, -200);
	label->SetFontSize(36);

	for (CUILabel* label : labels)
	{

	}

	this->engine = engine;
}

void CScoresState::clean(CEngine* engine)
{
	engine->entityManager->Clear();
}

void CScoresState::pause()
{
}

void CScoresState::resume()
{
}

void CScoresState::handleEvents(CEngine* engine)
{
}

void CScoresState::update(CEngine* engine)
{
	engine->entityManager->Tick();
	SDL_Delay((1000.0 / 60) - engine->deltaHelper->GetScaledDelta());
	checkSeque();
}

void CScoresState::draw(CEngine* engine)
{
	engine->drawManager->Tick(engine->renderer);
}

void CScoresState::input(CEngine* engine, SDL_Event* event)
{
	engine->inputManager->Tick(event);
}

void CScoresState::checkSeque()
{
	if (!shouldSeque) { return; }

	engine->stateManager->changeState(stateSeque, engine);
}

CScoresState::CScoresState(CEngine* engine)
{
	init(engine);
}

CScoresState::~CScoresState()
{
	delete background;
	background = nullptr;
}

void CScoresState::OnButtonClick(CUIButton* button)
{
	if (button->GetText() == "Terug")
	{
		shouldSeque = true;
		stateSeque = EGameState::Menu;
	}
}
