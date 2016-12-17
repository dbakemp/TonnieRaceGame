#include "SDL.h"
#include "CStateManager.h"
#include "CCamera.h"
#include "CLevelSelectorState.h"
#include "CDrawManager.h"
#include "CDeltaHelper.h"
#include "CInputManager.h"
#include "CEntityManager.h"
#include <curl/curl.h>
#include "CUIHorizontalScrollView.h"
#include "CUIImage.h"
#include "CUIButton.h"
#include "EUIAlignment.h"
#include <fstream>
#include <json/json.h>

void CLevelSelectorState::init(CEngine* engine)
{
	this->engine = engine;

	CUIImage* background = new CUIImage(engine, "Images/main.png");
	background->SetHorizontalAlignment(EUIALignmentHorizontal::CENTER);
	background->SetVerticalAlignment(EUIALignmentVertical::CENTER);
	background->SetVerticalStretch(EUIStretchVertical::FIT);

	scrollView = new CUIHorizontalScrollView(engine);
	scrollView->SetHorizontalAlignment(EUIALignmentHorizontal::CENTER);
	scrollView->SetVerticalAlignment(EUIALignmentVertical::CENTER);
	scrollView->SetWidth(600);
	scrollView->SetHeight(300);

	CUIButton* buttonBack = new CUIButton(engine, "Bangers", "Terug", "Images/terug.png");
	buttonBack->SetHorizontalAlignment(EUIALignmentHorizontal::LEFT);
	buttonBack->SetVerticalAlignment(EUIALignmentVertical::BOTTOM);
	buttonBack->SetPosition(100, -50);
	buttonBack->SetFontSize(30);
	buttonBack->SetClickCallback(std::bind(&CLevelSelectorState::OnButtonClick, this, std::placeholders::_1));

	CUIButton* buttonScrollLeft = new CUIButton(engine, "Bangers", "", "Images/scrollleft.png");
	buttonScrollLeft->SetHorizontalAlignment(EUIALignmentHorizontal::CENTER);
	buttonScrollLeft->SetVerticalAlignment(EUIALignmentVertical::CENTER);
	buttonScrollLeft->SetPosition(0 - (scrollView->GetRectangle().w / 2) - (buttonScrollLeft->GetRectangle().w / 2), 0);
	buttonScrollLeft->SetClickCallback(std::bind(&CLevelSelectorState::ScrollLeft, this));

	CUIButton* buttonScrollRight = new CUIButton(engine, "Bangers", "", "Images/scrollright.png");
	buttonScrollRight->SetHorizontalAlignment(EUIALignmentHorizontal::CENTER);
	buttonScrollRight->SetVerticalAlignment(EUIALignmentVertical::CENTER);
	buttonScrollRight->SetPosition(0 + (scrollView->GetRectangle().w / 2) + (buttonScrollRight->GetRectangle().w / 2), 0);
	buttonScrollRight->SetClickCallback(std::bind(&CLevelSelectorState::ScrollRight, this));


	std::string multiplayerText = "Multiplayer Off";
	if(engine->multiPlayer)
	{
		multiplayerText = "Multiplayer On";
	}
	multiplayerToggle = new CUIButton(engine, "Bangers", multiplayerText, "Images/rood.png");
	multiplayerToggle->SetHorizontalAlignment(EUIALignmentHorizontal::CENTER);
	multiplayerToggle->SetVerticalAlignment(EUIALignmentVertical::BOTTOM);
	multiplayerToggle->SetPosition(0, -50);
	multiplayerToggle->SetFontSize(23);
	multiplayerToggle->SetClickCallback(std::bind(&CLevelSelectorState::ToggleMultiplayer, this));

	Json::Value root;
	Json::Reader reader;

	std::ifstream stream("Resources/Maps/maps.json", std::ifstream::binary);
	if (reader.parse(stream, root, false))
	{
		for (Json::Value map : root["maps"])
		{
			addLevel("Maps/" + map.get("mapicon", "").asString(), map.get("mapname", "").asString());
		}
	}
}

void CLevelSelectorState::clean(CEngine* engine)
{
	engine->entityManager->Clear();
}

void CLevelSelectorState::addLevel(std::string image, std::string map)
{
	CUIImage* level = new CUIImage(engine, image);
	level->SetHorizontalAlignment(EUIALignmentHorizontal::CENTER);
	level->SetVerticalAlignment(EUIALignmentVertical::CENTER);
	level->SetTag(map);
	level->SetClickCallback(std::bind(&CLevelSelectorState::SelectLevel, this, placeholders::_1));

	scrollView->AddUIElement(level);
}

void CLevelSelectorState::SelectLevel(IUIEntity* entity)
{
	std::string map = entity->GetTag();
	engine->level = map;
	shouldSeque = true;
	stateSeque = EGameState::Playing;
}

void CLevelSelectorState::pause()
{
}

void CLevelSelectorState::resume()
{
}

void CLevelSelectorState::handleEvents(CEngine* engine)
{
}

void CLevelSelectorState::update(CEngine* engine)
{
	engine->entityManager->Tick();
	SDL_Delay((1000.0 / 120) - engine->deltaHelper->GetScaledDelta());
	checkSeque();
}

void CLevelSelectorState::draw(CEngine* engine)
{
	engine->drawManager->Tick(engine->renderer);
}

void CLevelSelectorState::input(CEngine* engine, SDL_Event* event)
{
	engine->inputManager->Tick(event);
}

void CLevelSelectorState::checkSeque()
{
	if (!shouldSeque) { return; }

	engine->stateManager->changeState(stateSeque, engine);
}

void CLevelSelectorState::ToggleMultiplayer()
{
	engine->multiPlayer = !engine->multiPlayer;

	if(engine->multiPlayer)
	{
		multiplayerToggle->SetText("Multiplayer On");
	} else
	{
		multiplayerToggle->SetText("Multiplayer Off");
	}
}

void CLevelSelectorState::ScrollLeft()
{
	scrollView->ScrollToPrevious();
}

void CLevelSelectorState::ScrollRight()
{
	scrollView->ScrollToNext();
}

CLevelSelectorState::CLevelSelectorState(CEngine* engine)
{
	init(engine);
}

CLevelSelectorState::~CLevelSelectorState()
{
}

void CLevelSelectorState::OnButtonClick(CUIButton* button)
{
	if (button->GetText() == "Terug")
	{
		shouldSeque = true;
		stateSeque = EGameState::Menu;
	}
}
