#pragma once
#include "Game.h"

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
	void createCamera();
	GAME_STATES update( SystemsSet &gameSystems, TimeData& time );
private:
};