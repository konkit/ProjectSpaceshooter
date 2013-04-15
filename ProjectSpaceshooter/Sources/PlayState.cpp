#include "GameState.h"
#include "PlayState.h"

#include "DebugDrawer.h"

#define THIRD_PERSON_CAMERA false
#define TWO_DIMENSION_CAMERA true

PlayState::PlayState(SystemsSet & gameSystems) :GameState()
{
	mSceneMgr = gameSystems.ogreManager.getRoot()->createSceneManager(Ogre::ST_GENERIC, "primary");
	createCamera();
	loadLevelDescribe(gameSystems);
	
	mSceneMgr->setSkyBox(true, "zygaBOX");

	//Init player's sceneNode
	Player* player = gameSystems.gameData.getPlayer();
	player->createSceneNode("smallfighter.MESH", mSceneMgr);
	
	//Create camera
	//Third person perspective camera
	if( THIRD_PERSON_CAMERA == true ) {
		Ogre::SceneNode *cameraNode = player->getSceneNode()->createChildSceneNode();
		cameraNode->attachObject(mCamera);			
		cameraNode->setPosition(Ogre::Vector3(0.0,20.0,-60.0));
		mCamera->lookAt(Ogre::Vector3(0,0,100));
	}
	else if ( TWO_DIMENSION_CAMERA == true ) {
	//2D like camera
//	Ogre::SceneNode *cameraNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
//		cameraNode->attachObject(mCamera);
//		cameraNode->setPosition(Ogre::Vector3(0.0, 2000.0, 0.0));
//		mCamera->lookAt(Ogre::Vector3(0.01, 0.01, 0.01));
	//2D like camera tied to player
		Ogre::SceneNode *cameraNode = player->getSceneNode()->createChildSceneNode();
		cameraNode->attachObject(mCamera);			
		cameraNode->setPosition(Ogre::Vector3(0.0,2000.0,-25.0));
		mCamera->lookAt(Ogre::Vector3(0.001,0.001,0.01));
	}

	//bullet model
	gameSystems.gameData.bulletEntity = mSceneMgr->createEntity("BulletEntity", "my_sun.MESH");

	//save node in player's GraphicsComponent
	//mGame->getGameData()->getPlayer()->initNode(mGame->getGameData()->shipNode);

	Ogre::SceneNode *stat = mSceneMgr->getRootSceneNode()->createChildSceneNode();
		//stat->attachObject(ship);
		stat->attachObject(gameSystems.gameData.bulletEntity);
		stat->setPosition(Ogre::Vector3(2400,0,100));
		//stat->pitch(Ogre::Degree(-90));
		stat->scale(2,2,2);

	gameSystems.gameData.setSceneMenagerFor(GAME_STATES::PLAY, mSceneMgr);

	// Set ambient light
	mSceneMgr->setAmbientLight(Ogre::ColourValue(1.0, 1.0, 1.0));

	// Create a light
	Ogre::Light* light = mSceneMgr->createLight("MainLight");
	light->setPosition(-50,50,0);
	light->setPowerScale(200.0);
	light = mSceneMgr->createLight("Light1");
	light->setPosition(-100,20,400);
	light->setPowerScale(200.0);
	light = mSceneMgr->createLight("Light2");
	light->setPosition(100,20,400);
	light->setPowerScale(200.0);
	//Ogre::Light* spotLight = mSceneMgr->createLight("AdditionalLight");
	//spotLight->setPosition(50,50,-200);
	//spotLight->setPowerScale(400.0);

	//Create tmp Core
	gameSystems.gameData.theCore.createSceneNode("core2.MESH", mSceneMgr);
	gameSystems.gameData.theCore.getSceneNode()->scale(35.0, 35.0, 35.0);
	gameSystems.gameData.theCore.setPosition(Ogre::Vector3(-500.0, 0.0, 0.0));
	gameSystems.gameData.theCore.getSceneNode()->roll(Ogre::Degree(90)); // BARDZO DUZA PROWIZORKA

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


void PlayState::loadLevelDescribe( SystemsSet & gameSystems )
{
	LevelDescription & _levelDescription = gameSystems.gameData.getLevelDescription();
	_levelDescription.ambientColour = Ogre::ColourValue(1.0f,1.0f,1.0f);
	Light * newLight = new Light;
	newLight->position = Vector3(100,100,100);
	_levelDescription.lightsCollections += newLight;

	LevelStage * newStage = new LevelStage;
	newStage->setStageNumber(1);
	newStage->setMissionType(missionType::destroyAllEnemy);

	EnemySpawner * newSpawner = new EnemySpawner(Vector3(100,0,400),10, 3);
	newSpawner->addEnemyToSpawn(1,3);
	newStage->addSpawner(newSpawner);
	
	newSpawner = new EnemySpawner(Vector3(-100,0,400),10,5);
	newSpawner->addEnemyToSpawn(1,4);
	newSpawner->setSpawnerDelaySinceStageStart(10);
	newStage->addSpawner(newSpawner);

	_levelDescription.addNewLevelStage(newStage);
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

