#pragma once
#include "PhysicsSystem.h"
#include "ObjectStateUpdateSystem.h"
#include "CollisionSystem.h"
#include "AISystem.h"
class PlayState : public GameState
{
private:
public:
	PlayState(SystemsSet & _systems);

	void setCamera( Player* player );

	~PlayState(){};
	virtual GAME_STATES update( SystemsSet & gameSystems, TimeData& time );
	void loadLevelDescribe( SystemsSet & gameSystems );
private:
	void createCamera();
	GAME_STATES nextState( SystemsSet &gameSystems );
	PhysicsSystem			mPhysicsSystem;
	ObjectStateUpdateSystem mObjectStateSystem;
	CollisionSystem			mCollisionSystem;
	AISystem				mAISystem;
};
