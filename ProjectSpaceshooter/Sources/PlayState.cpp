#include "GameState.h"
#include "PlayState.h"

#include "DebugDrawer.h"



PlayState::PlayState(SystemsSet & gameSystems) :GameState()
{
	mSceneMgr = gameSystems.ogreManager.getRoot()->createSceneManager(Ogre::ST_GENERIC, "primary");
	gameSystems.gameData.setSceneMenagerFor(GAME_STATES::PLAY, mSceneMgr);
	createCamera();
	gameSystems.gameData.setCameraFor(GAME_STATES::PLAY, mCamera);

	//System which draws primitives for debuging purposes
#ifdef _DEBUG
	new DebugDrawer(mSceneMgr, 0.5f);
#endif

	//Temporary explosion
	//Ogre::ParticleSystem* particleSystem = mSceneMgr->createParticleSystem("explosions", "explosionTemplate");

	//fast forward 1 second to the point where the particle has been emitted
	//particleSystem->fastForward(1.0);

	//attach the particle system to a scene node
	//Ogre::SceneNode *explosion = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	//explosion->attachObject(particleSystem);
	
}


GAME_STATES PlayState::update( SystemsSet & gameSystems, TimeData& time )
{
	//update input from player
	gameSystems.inputManager.updateInputForGame(gameSystems.gameData, time.deltaTime, time.currentTime);
	mAISystem.update(gameSystems.gameData, time.deltaTime);
	mPhysicsSystem.update( gameSystems.gameData, time.deltaTime );
	mCollisionSystem.update( gameSystems.gameData);
	mObjectStateSystem.update( gameSystems.gameData, time);

#ifdef _DEBUG
	DebugDrawer::getSingleton().build();
#endif

	renderOneFrame(gameSystems.ogreManager);

#ifdef _DEBUG
	DebugDrawer::getSingleton().clear();
#endif

	return nextState(gameSystems);

}

void PlayState::createCamera()
{
	// create the camera
	mCamera = mSceneMgr->createCamera("PlayerCam");
	// set its position, direction  
	// set the near clip distance
	mCamera->setNearClipDistance(5);
}


GAME_STATES PlayState::nextState( SystemsSet &gameSystems )
{
	if(gameSystems.gameData.isSetPauseFlag())
	{
		return GAME_STATES::PAUSE;
	} else
	{
		return GAME_STATES::PLAY;
	}
}

