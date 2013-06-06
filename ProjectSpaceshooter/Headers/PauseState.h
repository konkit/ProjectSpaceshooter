#pragma once
#include "TimeUtility.h"

/**
  * It's class for updating systems for pause
  *
  * @author Zyga
  */
class PauseState : public GameState
{
public:
	PauseState(SystemsSet & _systems);
	~PauseState(){};

	/** all updates of input systems are here */
	GAME_STATES update( SystemsSet &gameSystems, TimeData& time );

private:
	/** create the camera */
	void createCamera();

	/** returns the play state or pause state depending on input */
	GAME_STATES nextState( SystemsSet &gameSystems );
};