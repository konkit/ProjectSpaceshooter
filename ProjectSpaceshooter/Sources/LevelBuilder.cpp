#include "LevelBuilder.h"

#define THIRD_PERSON_CAMERA true
#define TWO_DIMENSION_CAMERA false

LevelBuilder::LevelBuilder( SystemsSet & gameSystems )
	:GameState()
{
	mGameData = &gameSystems.gameData;
	mSceneMgr = NULL;

}

LevelBuilder::~LevelBuilder()
{

}



GAME_STATES LevelBuilder::update( SystemsSet & gameSystems, TimeData& time )
{
	loadLevelDescribe(gameSystems);
	buildPlayScene(gameSystems, time);
	return nextState(gameSystems);
	
}

void LevelBuilder::loadLevelDescribe( SystemsSet & gameSystems )
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

void LevelBuilder::createCamera()
{
	throw std::exception("The method or operation is not implemented.");
}

GAME_STATES LevelBuilder::nextState( SystemsSet & gameSystems )
{
	return GAME_STATES::PLAY;
}

void LevelBuilder::buildPlayScene( SystemsSet & gameSystems, TimeData& time )
{
	Ogre::SceneManager * _sceneManager = mGameData->getSceneManagerFor(GAME_STATES::PLAY);
	_sceneManager->setSkyBox(true, "zygaBOX");

	//Init player's sceneNode
	Player * player = gameSystems.gameData.createPlayerFromPrefab(1);	
	createCameraNodeForPlayer(gameSystems);


	StaticObject *stat = mGameData->instantiateStatic(1);
	stat->setPosition(Vector3(100, 0,100));

	// Set ambient light
	_sceneManager->setAmbientLight(Ogre::ColourValue(1.0, 1.0, 1.0));

	// Create a light
	Ogre::Light* light = _sceneManager->createLight("MainLight");
	light->setPosition(-50,50,0);
	light->setPowerScale(200.0);
	light = _sceneManager->createLight("Light1");
	light->setPosition(-100,20,400);
	light->setPowerScale(200.0);
	light = _sceneManager->createLight("Light2");
	light->setPosition(100,20,400);
	light->setPowerScale(200.0);
	//Ogre::Light* spotLight = mSceneMgr->createLight("AdditionalLight");
	//spotLight->setPosition(50,50,-200);
	//spotLight->setPowerScale(400.0);
	
	//Create tmp Core
	Core * core = mGameData->createCore(2);
	core->setPosition(Vector3(-500,0,0));
}
void LevelBuilder::createCameraNodeForPlayer(SystemsSet & gameSystems)
{
	Ogre::Camera * _camera = gameSystems.gameData.getCameraFor(GAME_STATES::PLAY);
	Player * player = gameSystems.gameData.getPlayer();
	//Create camera
	//Third person perspective camera
	if( THIRD_PERSON_CAMERA == true ) {
		Ogre::SceneNode *cameraNode = player->getSceneNode()->createChildSceneNode();
		cameraNode->attachObject(_camera);			
		cameraNode->setPosition(Ogre::Vector3(0.0,20.0,-60.0));
		_camera->lookAt(Ogre::Vector3(0,0,100));
	}
	else if ( TWO_DIMENSION_CAMERA == true ) {
		//2D like camera
		//	Ogre::SceneNode *cameraNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
		//		cameraNode->attachObject(mCamera);
		//		cameraNode->setPosition(Ogre::Vector3(0.0, 2000.0, 0.0));
		//		mCamera->lookAt(Ogre::Vector3(0.01, 0.01, 0.01));
		//2D like camera tied to player
		Ogre::SceneNode *cameraNode = player->getSceneNode()->createChildSceneNode();
		cameraNode->attachObject(_camera);			
		cameraNode->setPosition(Ogre::Vector3(0.0,2000.0,-25.0));
		_camera->lookAt(Ogre::Vector3(0.001,0.001,0.01));
	}
}