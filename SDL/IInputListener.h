#ifndef IINPUTLISTENER_H 
#define IINPUTLISTENER_H

class CEngine;

class IInputListener {
public:
	virtual void Input() = 0;
	IInputListener(CEngine *engine);
	~IInputListener();
private:
	CEngine *engine;
};


#endif
