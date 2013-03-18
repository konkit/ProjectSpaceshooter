#include "GameState.h"

PlayState::PlayState( Game * game )
	:GameState(game)
{
	mSceneMgr = game->getOgreManager()->getRoot()->createSceneManager(Ogre::ST_GENERIC, "primary");
	createCamera();

	Ogre::Plane plane;
		plane.d = 2500;
		plane.normal = Ogre::Vector3::UNIT_Y;
	//mSceneMgr->setSkyPlane(true, plane, "Examples/SpaceSkyPlane", 1000, 45);
	mSceneMgr->setSkyBox(true, "Examples/SpaceSkyBox");

	//Init player's sceneNode
	Player* player = mGame->getGameData()->getPlayer();
	player->createSceneNode("smallfighter.MESH", mSceneMgr);
	
	//Create camera
	Ogre::SceneNode *cameraNode = player->getSceneNode()->createChildSceneNode();
		cameraNode->attachObject(mCamera);
		cameraNode->setPosition(Ogre::Vector3(0.0,20.0,-60.0));
	mCamera->lookAt(Ogre::Vector3(0,0,100));

	//bullet model
	mGame->getGameData()->bulletEntity = mSceneMgr->createEntity("BulletEntity", "rocket.MESH");

	//save node in player's GraphicsComponent
	//mGame->getGameData()->getPlayer()->initNode(mGame->getGameData()->shipNode);

	Ogre::SceneNode *stat = mSceneMgr->getRootSceneNode()->createChildSceneNode();
		//stat->attachObject(ship);
		stat->attachObject(mGame->getGameData()->bulletEntity);
		stat->setPosition(Ogre::Vector3(70,0,100));
		//stat->pitch(Ogre::Degree(-90));
		stat->scale(20,20,20);

	mGame->getGameData()->setSceneMenagerFor(GAME_STATES::PLAY, mSceneMgr);

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
}


bool PlayState::update( SystemsSet & gameSystems, TimeData& time )
{
	//update input from player
	gameSystems.mInputManager.updateInputForGame(gameSystems.mGameData, time.deltaTime, time.currentTime);
	mPhysicsSystem.update( gameSystems.mGameData, time.deltaTime );
	mCollisionSystem.update( gameSystems.mGameData);
	mObjectStateSystem.update( gameSystems.mGameData, time);

	//Render
	if( !gameSystems.mOgreManager.getRoot()->renderOneFrame() )	
	{
		throw WindowClosedException();
	}

	if(gameSystems.mGameData.isSetPauseFlag())
	{
		mGame->changeState(mGame->getPause());
	}
	return true;
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
	LevelDescription & _levelDescription = gameSystems.mGameData.getLevelDescription();
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

