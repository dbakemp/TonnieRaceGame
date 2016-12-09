#include "CLevelFactory.h"
#include "CDebugLogger.h"
#include "CEntityBorder.h"
#include "CEntityTile.h"
#include "CEntitySpawn.h"
#include "CEntityAd.h"
#include "CEntityCheckpoint.h"
#include "CEntityWaypoint.h"
#include "CEntityPowerup.h"
#include "CSpriteSheetManager.h"
#include "CTextureManager.h"
#include "SDL_image.h"
#include "SDL.h"
#include <poly2tri.h>
#include <vector>
#include <iostream>
#include <fstream>

CLevelFactory::CLevelFactory(CEngine* engine)
{
	this->engine = engine;
}

bool CLevelFactory::LoadMap(std::string path)
{
	CDebugLogger::PrintDebug("Loading Map");

	Json::Value root;
	Json::Reader reader;

	std::ifstream stream(path, std::ifstream::binary);
	if (reader.parse(stream, root, false))
	{
		CreateMap(&root);
		return true;
	}
	else
	{
		return false;
	}
}

void CLevelFactory::CreateMap(Json::Value* root)
{
	CDebugLogger::PrintDebug("Creating Map");

	map = new CMap();

	map->height = root->get("height", 0).asInt();
	map->width = root->get("width", 0).asInt();
	map->tileheight = root->get("tileheight", 0).asInt();
	map->tilewidth = root->get("tilewidth", 0).asInt();

	CDebugLogger::PrintDebug("Loading Spritesheets" + (map->spriteSheetLocation));
	SDL_Surface* texture = IMG_Load(map->spriteSheetLocation.c_str());
	map->spriteSheet = SDL_CreateTextureFromSurface(engine->renderer, texture);

	map->spriteSheetPowerUps = engine->textureManager->GetTexture("Spritesheets/spritesheet_powerups.png");

	CDebugLogger::PrintDebug("Loading Spritesheet");
	for (Json::Value spriteSheet : (*root)["tilesets"]) {
		CreateSpriteSheet(&spriteSheet);
	}

	CDebugLogger::PrintDebug("Itterating Layers");
	for (Json::Value layer : (*root)["layers"])
	{
		if (layer["type"].asString() == "objectgroup")
		{
			CreateObjects(&layer);
		}
		else if (layer["type"].asString() == "tilelayer")
		{
			CreateTiles(&layer);
		}
	}
}

void CLevelFactory::CreateObjects(Json::Value* root)
{
	CDebugLogger::PrintDebug("Creating Objects");

	CDebugLogger::PrintDebug("Itterating Objects");
	for (Json::Value object : (*root)["objects"])
	{
		if (object["type"].asString() == "wall")
		{
			CreateBorder(&object);
		}
		else if (object["type"].asString() == "spawn")
		{
			CreateSpawns(&object);
		}
		else if (object["type"].asString() == "checkpoint")
		{
			CreateCheckpoints(&object);
		}
		else if (object["type"].asString() == "waypoints")
		{
			CreateWaypoints(&object);
		}
		else if (object["type"].asString() == "powerup")
		{
			CreatePowerups(&object);
		}
		else if (object["type"].asString() == "ad")
		{
			CreateAd(&object);
		}
	}
}

void CLevelFactory::CreateTiles(Json::Value* root)
{
	CDebugLogger::PrintDebug("Creating Tiles");

	int number = 0;
	for (Json::Value tile : (*root)["data"])
	{
		if (tile.asInt() != 0)
		{
			new CEntityTile(this->engine, engine->spriteSheetManager->GetSpriteSheetByTileId(tile.asInt()) , tile.asInt(), number, map->width, map->height, map->tilewidth, map->tileheight);
		}
		number++;
	}
}

void CLevelFactory::CreateBorder(Json::Value* root)
{
	CDebugLogger::PrintDebug("Creating Border");

	const double scale = 5;
	const int verticesCount = (*root)["polygon"].size();

	std::vector<p2t::Point*> polyline;

	int i = 0;
	double xPos = (*root).get("x", 0).asDouble();
	double yPos = (*root).get("y", 0).asDouble();
	for (Json::Value polygon : (*root)["polygon"])
	{
		polyline.push_back(new p2t::Point((polygon.get("x", 0).asDouble() + xPos) / scale, (polygon.get("y", 0).asDouble() + yPos) / scale));
		i++;
	}

	p2t::CDT* cdt = new p2t::CDT(polyline);
	cdt->Triangulate();
	std::vector<p2t::Triangle*> triangles = cdt->GetTriangles();

	for (p2t::Triangle* triangle : triangles)
	{
		new CEntityBorder(this->engine, triangle);
	}
}

void CLevelFactory::CreateCheckpoints(Json::Value * root)
{
	CDebugLogger::PrintDebug("Creating Checkpoints");

	const double scale = 5;

	double xPos = (*root).get("x", 0).asDouble();
	double yPos = (*root).get("y", 0).asDouble();
	b2Vec2* start = new b2Vec2(((*root)["polyline"][0].get("x", 0).asDouble() + xPos) / scale, ((*root)["polyline"][0].get("y", 0).asDouble() + yPos) / scale);
	b2Vec2* end = new b2Vec2(((*root)["polyline"][1].get("x", 0).asDouble() + xPos) / scale, ((*root)["polyline"][1].get("y", 0).asDouble() + yPos) / scale);
	int index = (*root).get("properties", "").get("index", 0).asInt();

	bool isFinish = (*root).get("properties", "").get("isFinish", false).asBool();

	if (isFinish) {
		map->laps = (*root).get("properties", "").get("laps", 3).asInt();
	}

	map->checkpoints++;
	new CEntityCheckpoint(this->engine, start, end, index, isFinish);
}

void CLevelFactory::CreateWaypoints(Json::Value * root)
{
	CDebugLogger::PrintDebug("Creating Waypoints");

	const double scale = 5;
	double xPos = (*root).get("x", 0).asDouble();
	double yPos = (*root).get("y", 0).asDouble();

	int i = 0;
	for (Json::Value point : (*root)["polyline"])
	{
		CEntityWaypoint* waypoint = new CEntityWaypoint(engine, (point.get("x", 0).asDouble() + xPos) / scale, (point.get("y", 0).asDouble() + yPos) / scale, i);
		map->waypoints.push_back(waypoint);
		i++;
	}
}

void CLevelFactory::CreateAd(Json::Value * root)
{
	CDebugLogger::PrintDebug("Creating Ad");

	std::string direction = (*root).get("properties", "").get("direction", 0).asString();

	CAdManager::AdDirection directionEnum;

	if (direction == "down") {
		directionEnum = CAdManager::AdDirection::DOWN;
	}
	else if (direction == "up") {
		directionEnum = CAdManager::AdDirection::UP;
	}
	else if (direction == "right") {
		directionEnum = CAdManager::AdDirection::RIGHT;
	}
	else {
		directionEnum = CAdManager::AdDirection::LEFT;
	}

	CEntityAd* ad = new CEntityAd(engine, map, directionEnum);
	ad->tileX = (*root).get("x", 0).asDouble();
	ad->tileY = (*root).get("y", 0).asDouble();
	ad->textureHeight = (*root).get("height", 0).asDouble();
	ad->textureWidth = (*root).get("width", 0).asDouble();
}

void CLevelFactory::CreateSpriteSheet(Json::Value* root)
{

	if ((*root).get("columns", 0).asInt() != 0) {
		CSpriteSheetManager::SSpriteSheet* spriteSheet = new CSpriteSheetManager::SSpriteSheet();

		std::string location = (*root).get("properties", "").get("resourcepath", "").asString();

		spriteSheet->columns = (*root).get("columns", 0).asInt();
		spriteSheet->spacing = (*root).get("spacing", 0).asInt();
		spriteSheet->tileWidth = (*root).get("tilewidth", 0).asInt();
		spriteSheet->tileHeight = (*root).get("tileheight", 0).asInt();
		spriteSheet->width = (*root).get("imagewidth", 0).asInt();
		spriteSheet->height = (*root).get("imageheight", 0).asInt();
		spriteSheet->minTileIndex = (*root).get("firstgid", 0).asInt();
		spriteSheet->maxTileIndex = spriteSheet->minTileIndex+(*root).get("tilecount", 0).asInt()-1;

		spriteSheet->texture = engine->textureManager->GetTexture(location);

		engine->spriteSheetManager->AddSpriteSheet(spriteSheet);
	}
	else {
		int minIndex = (*root).get("firstgid", 0).asInt();
		int tileCount = (*root).get("tilecount", 0).asInt();
		for (int i = 0; i < tileCount; i++) {
			CSpriteSheetManager::SSpriteSheet* spriteSheet = new CSpriteSheetManager::SSpriteSheet();

			spriteSheet->columns = (*root).get("columns", 0).asInt();
			spriteSheet->spacing = (*root).get("spacing", 0).asInt();


			spriteSheet->minTileIndex = minIndex + i;
			spriteSheet->maxTileIndex = minIndex + i;
			std::string location = (*root)["tileproperties"].get(std::to_string(i), 0).get("resourcepath", 0).asString();

			spriteSheet->texture = engine->textureManager->GetTexture(location);

			SDL_QueryTexture(spriteSheet->texture, NULL, NULL, &spriteSheet->tileWidth, &spriteSheet->tileHeight);

			spriteSheet->width = spriteSheet->tileWidth;
			spriteSheet->height = spriteSheet->tileHeight;

			engine->spriteSheetManager->AddSpriteSheet(spriteSheet);
		}
	}

}

void CLevelFactory::CreateSpawns(Json::Value* root)
{
	CDebugLogger::PrintDebug("Creating Spawn");

	map->availableSpawns.push_back(new CEntitySpawn(engine, (*root).get("x", 0).asInt() / 5, (*root).get("y", 0).asInt() / 5));
}

void CLevelFactory::CreatePowerups(Json::Value* root) 
{
	CDebugLogger::PrintDebug("Creating Powerups");
	CEntityPowerup* powerup = new CEntityPowerup(engine, map, (*root).get("x", 0).asDouble(), (*root).get("y", 0).asDouble());
	map->powerups.push_back(powerup);
}
