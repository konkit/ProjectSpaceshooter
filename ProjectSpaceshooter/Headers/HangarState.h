#pragma once
#include "GameState.h"
#include "TimeUtility.h"
class HangarState : public GameState
{
public:
	HangarState(SystemsSet & gameSystems);
	~HangarState(){};

	virtual GAME_STATES update( SystemsSet & gameSystems, TimeData& time );

private:
	virtual void createCamera();
	virtual GAME_STATES nextState( SystemsSet & gameSystems );
};