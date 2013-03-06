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

void Game::run()
{
	while(true)
	{
		//get time
		float deltaTime = mOgreManager.getDeltaTime();

		//update input from player
		mInputManager.updateInput(mGameData, deltaTime);

		mPhysicsSystem.update( mGameData, deltaTime );
		state->update();

		mObjectStateSystem.update( mGameData, deltaTime );

		mGraphicsSystem.updateNodesAndDraw(mGameData);
	}
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

