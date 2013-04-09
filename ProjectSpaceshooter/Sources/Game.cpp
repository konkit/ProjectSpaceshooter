#include "Game.h"

Game::Game()
{
	
	initializeGame();
	mStateMenager.initStateManager(mGameSystems);
	resurceSystem.loadAllPrefabs(mGameSystems.gameData);
}

Game::~Game()
{
}

void Game::run()
{
	while(true)
	{
		//get time
		time.deltaTime = mGameSystems.ogreManager.getDeltaTime();
		time.currentTime = mGameSystems.ogreManager.getCurrentTime();

		mStateMenager.update(mGameSystems, time);
	}
}

void Game::initializeGame()
{
	//Initialize ogre
	mGameSystems.ogreManager.initOgre();
	//Initialize OIS
	mGameSystems.inputManager.initOIS( mGameSystems.ogreManager.getWindowHandle() );
}

