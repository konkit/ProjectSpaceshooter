#include "stdafx.h"
#include "StateManager.h"

StateManager::StateManager()
{
}


void StateManager::initStateManager( SystemsSet & gameSystems )
{
	pause = new PauseState(gameSystems);
	play = new PlayState(gameSystems);
	hangar = new HangarState(gameSystems);
	changeState(GAME_STATES::PLAY, gameSystems);
}


StateManager::~StateManager(void)
{
	delete pause;
	delete play;
	delete hangar;
}

bool StateManager::update( SystemsSet & gameSystems, TimeData& time )
{
	GAME_STATES nextState;
	nextState = activeState->update(gameSystems, time);
	if (nextState != activeStateName)
	{
		activeStateName = nextState;
		changeState(activeStateName, gameSystems);
	}
	return true;
}

void StateManager::changeState(GAME_STATES nextState, SystemsSet & gameSystems)
{
	activeState = getStateFor(nextState);
	gameSystems.gameData.setChangeToHangar(false);
	gameSystems.gameData.setChangeToMenu(false);
	gameSystems.gameData.setChangeToPause(false);
	gameSystems.gameData.setChangeToPlay(false);
	setupViewport(gameSystems.ogreManager, activeState->getCamera());
}

void StateManager::setupViewport( OgreManager & _ogreManager, Ogre::Camera * camera )
{
	_ogreManager.getWindowHandle()->removeAllViewports();
	// Create one viewport, entire window
	Ogre::Viewport* vp = _ogreManager.getWindowHandle()->addViewport(camera);
	//Set Background color
	vp->setBackgroundColour(Ogre::ColourValue(0,0,0));
	// Alter the camera aspect ratio to match the viewport
	camera->setAspectRatio(
		Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
}

GameState * StateManager::getStateFor( GAME_STATES nextState )
{
	switch (nextState)
	{
	case GAME_STATES::PLAY:
		return play;
	case GAME_STATES::PAUSE:
		return pause;
	case GAME_STATES::HANGAR:
		return hangar;
	default:
		return builder;
	}
}
