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

	void setCamera( Player* player );
	virtual GAME_STATES update( SystemsSet & gameSystems, TimeData& time );
	void loadLevelDescribe( SystemsSet & gameSystems );
private:
	void createCamera();
	GAME_STATES nextState( SystemsSet &gameSystems );



	int numOfFPS, currentFPSValue;
	float timeToOneSecond;

	DebugDrawer* cntDebugDrawer;
};
