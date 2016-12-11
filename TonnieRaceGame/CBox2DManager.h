#ifndef CBOX2DMANAGER_H
#define CBOX2DMANAGER_H
#include "SDL.h"
#include <Box2D\Box2D.h>
#include <vector>
#include "CEngine.h"

class IBox2DListener;

class CBox2DManager
{
public:
	CBox2DManager(CEngine* engine);
	std::vector<IBox2DListener*> listeners;

	void AddListener(IBox2DListener* box2DListener);
	void RemoveListener(IBox2DListener* box2DListener);
	void Tick(b2World* world);
	void Clear();

	~CBox2DManager();
private: 
	CEngine* engine;
};


#endif 
