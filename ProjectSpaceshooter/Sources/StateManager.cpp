#include "stdafx.h"
#include "StateManager.h"



StateManager::StateManager( SystemsSet * _systems )
{
	pause = new PauseState(_systems);
	play = new PlayState(_systems);
	hangar = new HangarState(_systems);
	changeState(play);

}


StateManager::~StateManager(void)
{
}

bool StateManager::update( SystemsSet & gameSystems, TimeData& time )
{

}

void StateManager::changeState( GAME_STATES * nextState )
{
	state = newState;
	mGameSystems.mGameData.setChangeToHangar(false);
	mGameSystems.mGameData.setChangeToMenu(false);
	mGameSystems.mGameData.setChangeToPause(false);
	mGameSystems.mGameData.setChangeToPlay(false);
	setupViewport(state->getCamera());
}

void StateManager::renderOneFrame()
{
	if( !mOgreManager->getRoot()->renderOneFrame() )	
	{
		throw WindowClosedException();
	}
}


void StateManager::setupViewport(Ogre::Camera * camera )
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
