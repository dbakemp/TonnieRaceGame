#include "CLevelFactory.h"
#include <iostream>
#include <fstream>
#include "CDebugLogger.h"
#include "CEntityBorder.h"
#include <poly2tri.h>
#include <vector>

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
	if (reader.parse(stream, root, false)) {
		CreateMap(&root);
		return true;
	}
	else {
		return false;
	}
}

void CLevelFactory::CreateMap(Json::Value* root)
{
	CDebugLogger::PrintDebug("Creating Map");

	map.height = root->get("height", 0).asInt();
	map.width = root->get("width", 0).asInt();
	map.tileheight = root->get("tileheight", 0).asInt();
	map.tilewidth = root->get("tilewidth", 0).asInt();

	CDebugLogger::PrintDebug("Itterating Layers");
	for (Json::Value layer : (*root)["layers"])
	{

		if (layer["type"].asString() == "objectgroup")
		{
			CreateObjects(&layer);
		}
		else if (layer["type"].asString() == "tilelayer") {
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
	}
}



void CLevelFactory::CreateTiles(Json::Value * root)
{
	CDebugLogger::PrintDebug("Creating Tiles");
}

void CLevelFactory::CreateBorder(Json::Value * root)
{
	CDebugLogger::PrintDebug("Creating Border");

	const int verticesCount = (*root)["polygon"].size();

	std::vector<p2t::Point*> polyline;

	int i = 0;
	double xPos = (*root).get("x", 0).asDouble();
	double yPos = (*root).get("y", 0).asDouble();
	for (Json::Value polygon : (*root)["polygon"])
	{
		polyline.push_back(new p2t::Point((polygon.get("x", 0).asDouble()+xPos)/4, (polygon.get("y", 0).asDouble()+yPos)/4));
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

