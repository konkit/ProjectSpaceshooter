#include "GameState.h"

void GameState::renderOneFrame( OgreManager & _ogreManager )
{
	if( !_ogreManager.getRoot()->renderOneFrame() )	
	{
		throw WindowClosedException();
	}
}