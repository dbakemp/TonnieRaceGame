#ifndef CLEVELFACTORY_H
#define CLEVELFACTORY_H

#include "CMap.h"
#include "CEngine.h"
#include <json\json.h>

class CLevelFactory
{
public:
	CLevelFactory(CEngine* engine);
	bool LoadMap(std::string path);
	void CreateMap(Json::Value* root);
	void CreateObjects(Json::Value* root);
	void CreateTiles(Json::Value* root);
	void CreateSpawns(Json::Value* root);
	void CreateBorder(Json::Value* root);
	void CreateCheckpoints(Json::Value* root);
	void CreateWaypoints(Json::Value* root);
	void CreateAd(Json::Value* root);
	CMap* map;
private:
	CEngine* engine;
};

#endif 
