#include "Game.h"
#include "GameState.h"
Game::Game()
{
	pause = new PauseState(this);
	play = new PlayState(this);
	hangar = new HangarState(this);
	state = play;
	initializeGame();
}

Game::~Game()
{
	delete pause; 
	delete play; 
	delete hangar;
}

bool Game::run()
{
	while(true)
	{
		//update input from player
		/* powinno byc updateInput( mGameData ) */
		if(mInputManager.updateInput(mGameData.camX, mGameData.camY, mGameData.camZ)==false)
			return false;

		//temporary game logic
		/* to powinno byc gdzies w jakims systemie */
		mGameData.mCamera->setPosition(Ogre::Vector3(mGameData.camX, mGameData.camY, mGameData.camZ));
		state->update();
		// Render a frame
		if(! mOgreManager.getRoot()->renderOneFrame()) return false;
	}

	return true;
}

void Game::initializeGame()
{
	//Initialize ogre
	mOgreManager.initOgre();
	//Initialize OIS
	mInputManager.initOIS( mOgreManager.getWindowHandle() );

	//Initialize scene - setup all cameras, entities, etc
	mGameData.initScene( mOgreManager.getRoot(), mOgreManager.getWindowHandle() );
	mGameData.setScene();
}

