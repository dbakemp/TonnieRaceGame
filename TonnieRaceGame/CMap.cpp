#include "CMap.h"
#include "CEntityCar.h"
#include <algorithm>

struct PostitionSort
{
	PostitionSort(CEngine* engine)
	{
		this->engine = engine;
	}

	bool operator() (CEntityCar* carA, CEntityCar* carB) {
		if (carA->currentLap < carB->currentLap)
		{
			return false;
		}
		else if (carA->currentCheckpoint < carB->currentCheckpoint)
		{
			return false;
		}
		else
		{
			b2AABB aabb;
			aabb.lowerBound = b2Vec2(FLT_MAX, FLT_MAX);
			aabb.upperBound = b2Vec2(-FLT_MAX, -FLT_MAX);
			b2Fixture* fixture = engine->currentMap->GetCheckpointByIndex(carA->currentCheckpoint)->body->GetFixtureList();
			while (fixture != NULL)
			{
				aabb.Combine(aabb, fixture->GetAABB(0));
				fixture = fixture->GetNext();
			}

			b2Vec2 veca = { (carA->aabb.lowerBound.x + carA->aabb.upperBound.x) / 2, (carA->aabb.lowerBound.y + carA->aabb.upperBound.y) / 2 };
			b2Vec2 vecb = { (aabb.lowerBound.x + aabb.upperBound.x) / 2, (aabb.lowerBound.y + aabb.upperBound.y) / 2 };
			b2Vec2 vecc = veca - vecb;

			float distancea = vecc.Normalize();

			b2Vec2 vecd = { (carB->aabb.lowerBound.x + carB->aabb.upperBound.x) / 2, (carB->aabb.lowerBound.y + carB->aabb.upperBound.y) / 2 };
			b2Vec2 vecf = vecd - vecb;

			float distanceb = vecf.Normalize();

			if (distancea < distanceb)
			{
				return false;
			}
		}
		return true;
	}

	CEngine* engine;
};

CMap::CMap(CEngine* engine)
{
	this->engine = engine;
}

CMap::~CMap()
{
	for (CEntitySpawn* spawn : availableSpawns)
	{
		spawn = nullptr;
	}
	for (CEntitySpawn* spawn : takenSpawns)
	{
		spawn = nullptr;
	}
	availableSpawns.clear();
	takenSpawns.clear();
	cars.clear();
}

void CMap::CheckPositions()
{
	std::sort(cars.begin(), cars.end(), PostitionSort(engine));

	for (int i = 0; i < cars.size(); i++)
	{
		cars[i]->SetPosition(i+1);
	}
}

CEntityCheckpoint* CMap::GetCheckpointByIndex(int index)
{
	if(index >= checkpoints || index <= -1)
	{
		return checkpointsList.at(0);
	}
	return checkpointsList.at(index);
}

CEntitySpawn* CMap::GetSpawn()
{
	CEntitySpawn* spawn = availableSpawns.front();
	availableSpawns.erase(availableSpawns.begin());
	takenSpawns.push_back(spawn);

	return spawn;
}
