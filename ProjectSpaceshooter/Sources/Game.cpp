#include "Game.h"


Game::Game()
{
	
	initializeGame();
	
}

Game::~Game()
{
}

void Game::run()
{
	while(true)
	{
		//get time
		time.deltaTime = mGameSystems.mOgreManager.getDeltaTime();
		time.currentTime = mGameSystems.mOgreManager.getCurrentTime();

		mGameSystems.update(mGameSystems, time);
	}
}

void Game::initializeGame()
{
	//Initialize ogre
	mGameSystems.mOgreManager.initOgre();
	//Initialize OIS
	mGameSystems.mInputManager.initOIS( mGameSystems.mOgreManager.getWindowHandle() );
}


void Game::changeState( GameState * newState )
{

}

