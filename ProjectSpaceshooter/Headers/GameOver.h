#pragma once
#include "GameState.h"

/** Gameover state - in use when player is dead. Shows explosion of player and score. 
  * @author Zyga
  */
class GameOver : public GameState
{
public:
	GameOver( SystemsSet & gameSystems );
	virtual ~GameOver();

	/** all updates of input systems are here */
	virtual GAME_STATES update( SystemsSet & gameSystems, TimeData& time );

	/** moves camera to show your own explosion */
	void setDeadCamera( SystemsSet &gameSystems );
	
	virtual void createCamera();

	/** return next state - current or hangar */
	virtual GAME_STATES nextState( SystemsSet & gameSystems );
	bool deadCamera;
private:

};