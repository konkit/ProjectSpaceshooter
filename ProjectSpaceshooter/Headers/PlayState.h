#pragma once
#include "Game.h"
class PlayState : public GameState
{
private:
public:
	PlayState(Game * game);

	void createCamera();

	~PlayState(){};

	virtual bool update( SystemsSet & gameSystems, TimeData& time );
	void loadLevelDescribe( SystemsSet & gameSystems );

private:
	PhysicsSystem			mPhysicsSystem;

	ObjectStateUpdateSystem mObjectStateSystem;
};
