#include "GameState.h"

PlayState::PlayState( Game * game )
	:GameState(game)
{

}

bool PlayState::update()
{
	game->getGameData()->ShipNode->yaw(Ogre::Degree(0.2));
	return true;
}
