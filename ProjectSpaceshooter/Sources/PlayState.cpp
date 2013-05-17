#include "GameState.h"
#include "PlayState.h"




PlayState::PlayState(SystemsSet & gameSystems) :GameState()
{
    mSceneMgr = gameSystems.ogreManager.getRoot()->createSceneManager(Ogre::ST_GENERIC, "primary");
    gameSystems.gameData.setSceneMenagerFor(GAME_STATES::PLAY, mSceneMgr);
    createCamera();
    gameSystems.gameData.setCameraFor(GAME_STATES::PLAY, mCamera);

    //System which draws primitives for debuging purposes
#ifdef _DEBUG
    gameSystems.cntDebugDrawer = new DebugDrawer(mSceneMgr, 0.5f);
#endif

    //Temporary explosion
    //Ogre::ParticleSystem* particleSystem = mSceneMgr->createParticleSystem("explosions", "explosionTemplate");

    //fast forward 1 second to the point where the particle has been emitted
    //particleSystem->fastForward(1.0);

    //attach the particle system to a scene node
    //Ogre::SceneNode *explosion = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    //explosion->attachObject(particleSystem);

    numOfFPS = 0;
    timeToOneSecond = 0.0;

    //Initialize GUI system
	gameSystems.mGUISystem.init( mSceneMgr );
}


GAME_STATES PlayState::update( SystemsSet & gameSystems, TimeData& time )
{
    timeToOneSecond += time.deltaTime;
    if( timeToOneSecond > 1.0 ) {
        time.currentFPSValue = numOfFPS;
        numOfFPS = 0;
        timeToOneSecond = 0.0;

  //      std::cout<<"FPS : "<<time.currentFPSValue<<"\n";
    }

    numOfFPS++;

    //update input from player
    gameSystems.inputManager.updateInputForGame(gameSystems.gameData, time.deltaTime, time.currentTime);
    gameSystems.mAISystem.update(gameSystems.gameData, time);
    gameSystems.mPhysicsSystem.update( gameSystems.gameData, time.deltaTime );
    gameSystems.mCollisionSystem.update( gameSystems.gameData);
    gameSystems.mObjectStateSystem.update( gameSystems.gameData, time);

	gameSystems.mGUISystem.display(gameSystems.gameData, time);

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
	GameData & gameData = gameSystems.gameData;
	if (gameData.isPlayerDead() || gameData.isCoreDead())
	{
	
		return GAME_STATES::GAME_OVER;
	} else if(gameSystems.gameData.isSetPauseFlag())
    {
        return GAME_STATES::PAUSE;
    } else
    {
        return GAME_STATES::PLAY;
    }
}

