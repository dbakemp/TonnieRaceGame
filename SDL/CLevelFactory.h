#ifndef CLEVELFACTORY_H
#define CLEVELFACTORY_H

#include "CMap.h"
#include "CEngine.h"
#include <json\json.h>
#include <string>

class CLevelFactory
{
public:
	CLevelFactory(CEngine* engine);
	bool LoadMap(std::string path);
	void CreateMap(Json::Value* root);
	void CreateObjects(Json::Value* root);
	void CreateTiles(Json::Value* root);
	void CreateBorder(Json::Value* root);
private:
	CEngine* engine;
	CMap* map;
};

#endif 
