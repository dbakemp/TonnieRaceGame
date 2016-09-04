#ifndef CDINPUTMANAGER_H
#define CDINPUTMANAGER_H
#include <vector>

class IInputListener;

class CInputManager {
public:
	std::vector<IInputListener*> listeners;

	void AddListener(IInputListener *inputListener);
	void RemoveListener(IInputListener *inputListener);
	void Tick();
};


#endif