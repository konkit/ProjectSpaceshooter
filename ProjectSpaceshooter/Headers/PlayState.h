#pragma once
#include "PhysicsSystem.h"
#include "ObjectStateUpdateSystem.h"
#include "CollisionSystem.h"
#include "AISystem.h"

#include "DebugDrawer.h"
#include "TimeUtility.h"

class PlayState : public GameState
{
private:
public:
	PlayState(SystemsSet & _systems);
	~PlayState()
	{
	}

	void setCamera( Player* player );
	virtual GAME_STATES update( SystemsSet & gameSystems, TimeData& time );
	void loadLevelDescribe( SystemsSet & gameSystems );
private:
	void createCamera();
	GAME_STATES nextState( SystemsSet &gameSystems );



	int numOfFPS, currentFPSValue;
	float timeToOneSecond;
};
