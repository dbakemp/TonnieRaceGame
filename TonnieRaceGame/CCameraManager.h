#ifndef CCAMERAMANAGER_H
#define CCAMERAMANAGER_H
#include "SDL.h"
#include "CEngine.h"
#include "CCamera.h"
#include <vector>

class CCameraManager
{
public:
	CCameraManager(CEngine* engine);
	~CCameraManager();

	int Count();
	CCamera* GetNextCamera();
	CCamera* GetCameraByIndex(int index);
	CCamera* GetCurrentCamera();
	void AddCamera();
	void Update();
	void UpdateViewPort();
	void ClearAll();
private:
	CEngine* engine;
	std::vector<CCamera*> cameraList;
	CCamera* currentCamera;
	int currentCameraIndex;
	int count;
};


#endif 
