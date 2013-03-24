#pragma once
#include "Game.h"
class PlayState : public GameState
{
private:
public:
	PlayState(SystemsSet & _systems);
	void createCamera();

	~PlayState(){};

	virtual GAME_STATES update( SystemsSet & gameSystems, TimeData& time );
	void loadLevelDescribe( SystemsSet & gameSystems );

private:
	PhysicsSystem			mPhysicsSystem;
	ObjectStateUpdateSystem mObjectStateSystem;
	CollisionSystem			mCollisionSystem;
	AISystem				mAISystem;
};
