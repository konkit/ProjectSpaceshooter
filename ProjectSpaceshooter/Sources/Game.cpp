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
		if(! mOgreManager.getRoot()->renderOneFrame()) return false;


					//update input from player
			/* powinno byc updateInput( mGameData ) */
			if(mInputManager.updateInput(mGameData)==false)
				return false;

			//std::cout<<"Player velocity = "<<mGameData.getPlayer()->getPhysicsComponent().velocityX<<", "<<
			//								mGameData.getPlayer()->getPhysicsComponent().velocityY<<", "<<
			//								mGameData.getPlayer()->getPhysicsComponent().velocityZ<<"\n";

			// game logic
			/* tu powinny byæ wszystkie update'y systemów
			   aiSystem.update( mGameData );
			   physicsSystem.update( mGameData );
			   collisionSystem.update( mGameData );*/

			mPhysicsSystem.update( mGameData );


			mGraphicsSystem.updateNodesAndDraw(mGameData);

			//std::cout<<"Player pos = "<<mGameData.getPlayer()->getTransformComponent().getX()<<", "<<
			//							mGameData.getPlayer()->getTransformComponent().getY()<<", "<<
			//							mGameData.getPlayer()->getTransformComponent().getZ()<<"\n";
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

