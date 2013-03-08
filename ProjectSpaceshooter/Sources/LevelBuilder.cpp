#include "GameState.h"

LevelBuilder::LevelBuilder( Game * game )
	:GameState(game)
{

}

LevelBuilder::~LevelBuilder()
{

}


bool LevelBuilder::update( SystemsSet & gameSystems, TimeData time )
{
	throw std::exception("The method or operation is not implemented.");
	return true;
}
