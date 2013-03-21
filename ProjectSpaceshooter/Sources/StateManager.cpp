#include "stdafx.h"
#include "StateManager.h"


StateManager::StateManager(void)
{
	pause = new PauseState(this);
	play = new PlayState(this);
	hangar = new HangarState(this);
	changeState(play);
}


StateManager::~StateManager(void)
{
}

bool StateManager::update( SystemsSet & gameSystems, TimeData& time )
{

}
