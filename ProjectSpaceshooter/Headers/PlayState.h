#pragma once
#include "PhysicsSystem.h"
#include "ObjectStateUpdateSystem.h"
#include "CollisionSystem.h"
#include "AISystem.h"

#include "DebugDrawer.h"

class PlayState : public GameState
{
private:
public:
	PlayState(SystemsSet & _systems);
	~PlayState()
	{
#ifdef _DEBUG
	cntDebugDrawer->clear();
	delete cntDebugDrawer;
#endif
	}

	virtual GAME_STATES update( SystemsSet & gameSystems, TimeData& time );
	void loadLevelDescribe( SystemsSet & gameSystems );
private:
	void createCamera();
	GAME_STATES nextState( SystemsSet &gameSystems );
	PhysicsSystem			mPhysicsSystem;
	ObjectStateUpdateSystem mObjectStateSystem;
	CollisionSystem			mCollisionSystem;
	AISystem				mAISystem;


	int numOfFPS, currentFPSValue;
	float timeToOneSecond;

	DebugDrawer* cntDebugDrawer;
};
