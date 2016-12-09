#ifndef CENTITYCARAI_H
#define CENTITYCARAI_H

#include "IDrawListener.h"
#include "IInputListener.h"
#include "IBox2DListener.h"
#include "ILapCountable.h"
#include "CEngine.h"
#include "CEntity.h"
#include "CEntityWaypoint.h"
#include "CEntityCheckpoint.h"
#include "CGAState.h"
#include <vector>
#include <Box2D\Box2D.h>
#include <functional>
#include <bitset>

class CEntityTireAI;
class CMap;
typedef void (CGAState::*Callback)();

class CEntityCarAI : public CEntity, public IDrawListener, public IBox2DListener, public ILapCountable
{
public:
	struct CarGenetics {
		float carDensity = 0.1f;
		float slowDownBias = 0.8f;
		int maxForwardSpeed = 600;
		int maxDriveForce = 500;
		float angularImpulseBias = 0.1f;
		int dragForceBias = 3;
		int desiredTorque = 15;

		void GetBitString();
		void SetBitString(std::string bitString);
	};

	CEntityCarAI(CEngine* engine, CMap* map);
	void Draw(SDL_Renderer* renderer);
	void Update();
	void Create(b2World* world);
	b2RevoluteJoint *flJoint, *frJoint;
	std::vector<CEntityTireAI*> tires;
	void CollisionBegin(CEntity* collider) override;
	void CollisionEnd(CEntity* collider) override;
	void ProcessCheckpoint(CEntityCheckpoint* checkpoint);
	void ProcessWaypoint(CEntityWaypoint* waypoint);
	void ChangeWaypoint(CEntityWaypoint* waypoint);
	void SetFinishCallback(std::function<void(IBox2DListener*)> callback);
	void FinishCallback();


	int currentWaypoint;
	int biasX, biasY;
	double backupTimer;
	double backingupTimer;
	bool shouldBackup;

	CEntityWaypoint* heading;

	SDL_Texture* spriteSheet;
	SDL_Rect srcRect;
	std::function<void(IBox2DListener*)> finishCallback;

	CarGenetics* carGenetics;
private:
	CEngine* engine;
};

#include "CEntityTireAI.h"
#endif
