#include "CCameraManager.h"

CCameraManager::CCameraManager(CEngine * engine)
{
	this->currentCamera = nullptr;
	this->currentCameraIndex = 0;
	this->count = 0;

	this->engine = engine;
}

CCameraManager::~CCameraManager()
{
}

int CCameraManager::Count()
{
	return count;
}

CCamera* CCameraManager::GetNextCamera()
{
	if (count <= 0) { return nullptr; }

	if (currentCameraIndex >= count) {
		currentCameraIndex = 0;
	}

	currentCamera = GetCameraByIndex(currentCameraIndex);
	currentCameraIndex++;

	return currentCamera;
}

CCamera* CCameraManager::GetCameraByIndex(int index)
{
	if (index < cameraList.size() && index >= 0) {
		return cameraList.at(index);
	}

	return nullptr;
}

CCamera * CCameraManager::GetCurrentCamera()
{
	return currentCamera;
}

void CCameraManager::AddCamera()
{
	cameraList.push_back(new CCamera(engine));
	count++;

	if (currentCamera == nullptr) {
		currentCamera = GetCameraByIndex(0);
	}
	UpdateViewPort();
}

void CCameraManager::Update()
{
	for (CCamera* camera : cameraList) {
		camera->Update();
	}
}

void CCameraManager::UpdateViewPort()
{
	int width = engine->windowWidth / count;
	int height = engine->windowHeight;
	int index = 0;

	for (CCamera* camera : cameraList) {
		camera->SetViewPort(width, height, index*width, 0);
		index++;
	}
}

void CCameraManager::ClearAll()
{
	for (CCamera* camera : cameraList) {
		delete camera;
	}
	cameraList.clear();
	count = 0;
}
