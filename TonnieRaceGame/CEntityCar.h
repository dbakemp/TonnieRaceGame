#ifndef CENTITYCAR_H
#define CENTITYCAR_H

#include "IDrawListener.h"
#include "IInputListener.h"
#include "IBox2DListener.h"
#include "ILapCountable.h"
#include "CEntity.h"
#include "CEngine.h"
#include "CEntityParticleEmitter.h"
#include "CEntityTire.h"
#include "CEntityCheckpoint.h"
#include "CEntityPowerup.h"
#include <vector>
#include <Box2D\Box2D.h>
#include <functional>
#include "IControlScheme.h"

class CMap;

class CEntityCar : public CEntity, public IDrawListener, public IInputListener, public IBox2DListener, public ILapCountable
{
public:
	CEntityCar(CEngine* engine, CMap* map);
	~CEntityCar();
	void Draw(SDL_Renderer* renderer);
	void Input(SDL_Event* event);
	void Update();
	void Create(b2World* world);
	b2RevoluteJoint *flJoint, *frJoint;
	std::vector<CEntityTire*> tires;
	void OnControllerAxis(const SDL_ControllerAxisEvent sdlEvent);
	void CollisionBegin(CEntity* collider) override;
	void CollisionEnd(CEntity* collider) override;
	void ProcessCheckpoint(CEntityCheckpoint* checkpoint);
	void ActivatePowerup(CEntityPowerup* powerup);
	void ProcessWaypoint(CEntityWaypoint* waypoint);
	void ChangeWaypoint(CEntityWaypoint* waypoint);
	double powerupTimer;
	bool powerupActive;
	void SetFinishCallback(std::function<void(IBox2DListener*)> callback);
	void FinishCallback();
	void SetControlScheme(IControlScheme* controlScheme);
	void SetPosition(int position);
	int GetPosition();

	SDL_Texture* spriteSheet;
	SDL_Rect srcRect;
	CEntityPowerup* activePowerup;
	CEntityParticleEmitter* emitter;
	b2AABB aabb;

	CEntityWaypoint* heading;

	int currentWaypoint;
	int biasX, biasY;
	double backupTimer;
	double backingupTimer;
	bool shouldBackup;
private:
	CEngine* engine;
	std::function<void(IBox2DListener*)> finishCallback;
	IControlScheme* controlScheme;
	int position;
};

#endif
