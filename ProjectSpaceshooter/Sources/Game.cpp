#include "Game.h"
#include "GameState.h"
Game::Game()
{
	initializeGame();
	pause = new PauseState(this);
	play = new PlayState(this);
	hangar = new HangarState(this);
	changeState(pause);
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
			state->update();

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

	mGraphicsSystem.init(&mOgreManager);

}

void Game::setupViewport(Ogre::Camera * camera )
{
	mOgreManager.getWindowHandle()->removeAllViewports();
	// Create one viewport, entire window
	Ogre::Viewport* vp = mOgreManager.getWindowHandle()->addViewport(camera);
	//Set Background color
	vp->setBackgroundColour(Ogre::ColourValue(0,0,0));
	// Alter the camera aspect ratio to match the viewport
	camera->setAspectRatio(
		Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
}

void Game::changeState( GameState * newState )
{
	state = newState;
	setupViewport(state->getCamera());
}

