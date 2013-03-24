#include "GameState.h"

PauseState::PauseState( Game * game )
	:GameState(game)
{
}

PauseState::PauseState( SystemsSet & _systems )
	: GameState()
{
	mSceneMgr = _systems->mOgreManager->getRoot()->createSceneManager(Ogre::ST_GENERIC, "pause");
	createCamera();

	Ogre::Entity* ogreHead = mSceneMgr->createEntity("Head", "smallfighter.MESH");
	Ogre::Plane plane;
	plane.d = 2500;
	plane.normal = Ogre::Vector3::UNIT_Y;
	//mSceneMgr->setSkyPlane(true, plane, "Examples/SpaceSkyPlane", 1000, 45);
	mSceneMgr->setSkyBox(true, "Examples/SpaceSkyBox");
	//create sceneNode for player
	Ogre::SceneNode * shipNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	//attach model to that node
	shipNode->attachObject(ogreHead);
	//save node in player's GraphicsComponent
	shipNode->yaw(Ogre::Degree(10));
	shipNode->roll(Ogre::Degree(10));
	// Set ambient light
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));

	// Create a light
	Ogre::Light* light = mSceneMgr->createLight("MainLight");
	light->setPosition(-50,50,0);
	light->setPowerScale(200.0);

}


/**
* It's main method for pause state. This method update input system and render next frame
* @return GAME_STATES - return next game state
* @param SystemsSet & gameSystems
* @param TimeData & time
* @author Zyga 
*/GAME_STATES PauseState::update( SystemsSet &gameSystems, TimeData& time )
{
	gameSystems.mInputManager.updateInputForPause(gameSystems.mGameData);

	//render
	if( !gameSystems.mOgreManager.getRoot()->renderOneFrame() )	
	{
		throw WindowClosedException();
	}

	if(gameSystems.mGameData.isSetPlayFlag())
	{
		return GAME_STATES::PLAY;
	}
	return GAME_STATES::PAUSE;	
}

void PauseState::createCamera()
{
	// create the camera
	mCamera = mSceneMgr->createCamera("PlayerCam");
	// set its position, direction  
	mCamera->setPosition(Ogre::Vector3(0.0,30.0,50.0));
	mCamera->lookAt(Ogre::Vector3(0,1.0,1.0));
	// set the near clip distance
	mCamera->setNearClipDistance(5);
}
