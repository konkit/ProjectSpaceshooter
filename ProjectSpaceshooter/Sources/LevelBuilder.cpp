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
	loadLevelDescribe(gameSystems);
	return true;
}

void LevelBuilder::loadLevelDescribe( SystemsSet & gameSystems )
{

}
