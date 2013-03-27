#include "GameState.h"


HangarState::HangarState( SystemsSet & gameSystems )
	:GameState()
{

}


GAME_STATES HangarState::update( SystemsSet & gameSystems, TimeData& time )
{
	throw std::exception("The method or operation is not implemented.");
}

void HangarState::createCamera()
{
	throw std::exception("The method or operation is not implemented.");
}

GAME_STATES HangarState::nextState( SystemsSet & gameSystems )
{
	throw std::exception("The method or operation is not implemented.");
}
