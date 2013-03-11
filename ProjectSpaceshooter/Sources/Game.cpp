#include "Game.h"
#include "GameState.h"

Game::Game()
{
	
	initializeGame();
	pause = new PauseState(this);
	play = new PlayState(this);
	hangar = new HangarState(this);
	changeState(play);
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
		time.deltaTime = mGameSystems.mOgreManager.getDeltaTime();
		time.currentTime = mGameSystems.mOgreManager.getCurrentTime();

		state->update(mGameSystems, time);
	}
}

void Game::initializeGame()
{
	//Initialize ogre
	mGameSystems.mOgreManager.initOgre();
	//Initialize OIS
	mGameSystems.mInputManager.initOIS( mGameSystems.mOgreManager.getWindowHandle() );
	mGameSystems.mGraphicsSystem.init(&mGameSystems.mOgreManager); // TODO change to systemset
}

void Game::setupViewport(Ogre::Camera * camera )
{
	mGameSystems.mOgreManager.getWindowHandle()->removeAllViewports();
	// Create one viewport, entire window
	Ogre::Viewport* vp = mGameSystems.mOgreManager.getWindowHandle()->addViewport(camera);
	//Set Background color
	vp->setBackgroundColour(Ogre::ColourValue(0,0,0));
	// Alter the camera aspect ratio to match the viewport
	camera->setAspectRatio(
		Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
}

void Game::changeState( GameState * newState )
{
	state = newState;
	mGameSystems.mGameData.setChangeToHangar(false);
	mGameSystems.mGameData.setChangeToMenu(false);
	mGameSystems.mGameData.setChangeToPause(false);
	mGameSystems.mGameData.setChangeToPlay(false);
	setupViewport(state->getCamera());
}

