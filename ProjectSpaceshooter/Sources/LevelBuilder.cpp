#include "LevelBuilder.h"

LevelBuilder::LevelBuilder( SystemsSet & gameSystems )
	:GameState()
{

}

LevelBuilder::~LevelBuilder()
{

}


bool LevelBuilder::update( SystemsSet & gameSystems, TimeData time )
{
	loadLevelDescribe(gameSystems);
	return true;
}

GAME_STATES LevelBuilder::update( SystemsSet & gameSystems, TimeData& time )
{
	throw std::exception("The method or operation is not implemented.");
}

void LevelBuilder::loadLevelDescribe( SystemsSet & gameSystems )
{

}

void LevelBuilder::createCamera()
{
	throw std::exception("The method or operation is not implemented.");
}

GAME_STATES LevelBuilder::nextState( SystemsSet & gameSystems )
{
	throw std::exception("The method or operation is not implemented.");
}
