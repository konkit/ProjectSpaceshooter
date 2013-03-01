#include "GameState.h"

LevelBuilder::LevelBuilder( Game * game )
	:GameState(game)
{

}

LevelBuilder::~LevelBuilder()
{

}

bool LevelBuilder::update()
{
	return true;
}
