#include "CLevelFactory.h"
#include "CDebugLogger.h"
#include "CEntityBorder.h"
#include "CEntityTile.h"
#include "CEntitySpawn.h"
#include "CEntityAd.h"
#include "CEntityCheckpoint.h"
#include "CEntityWaypoint.h"
#include "CEntityPowerup.h"
#include "SDL_image.h"
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
	map->spriteSheetLocation = (*root)["tilesets"][0].get("properties", "").get("resourcepath", "").asString();
	map->spriteSheetColumns = (*root)["tilesets"][0].get("columns", 0).asInt();
	map->spriteSheetSpacing = (*root)["tilesets"][0].get("spacing", 0).asInt();
	map->spriteSheetTileWidth = (*root)["tilesets"][0].get("tilewidth", 0).asInt();
	map->spriteSheetTileHeight = (*root)["tilesets"][0].get("tileheight", 0).asInt();
	map->spriteSheetWidth = (*root)["tilesets"][0].get("imagewidth", 0).asInt();
	map->spriteSheetHeight = (*root)["tilesets"][0].get("imageheight", 0).asInt();

	CDebugLogger::PrintDebug("Loading Spritesheets" + (map->spriteSheetLocation));
	SDL_Surface* texture = IMG_Load(map->spriteSheetLocation.c_str());
	map->spriteSheet = SDL_CreateTextureFromSurface(engine->renderer, texture);

	SDL_Surface* texturePowerups = IMG_Load("Resources/Spritesheets/spritesheet_powerups.png");
	map->spriteSheetPowerUps = SDL_CreateTextureFromSurface(engine->renderer, texturePowerups);

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
<<<<<<< HEAD
		else if (object["type"].asString() == "powerup") 
		{
			CreatePowerups(&object);
=======
		else if (object["type"].asString() == "ad")
		{
			CreateAd(&object);
>>>>>>> master
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
			new CEntityTile(this->engine, this->map, tile.asInt(), number);
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
	CEntityAd* ad = new CEntityAd(engine, map);
	ad->tileX = (*root).get("x", 0).asDouble();
	ad->tileY = (*root).get("y", 0).asDouble();
	ad->textureHeight = (*root).get("height", 0).asDouble();
	ad->textureWidth = (*root).get("width", 0).asDouble();
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
