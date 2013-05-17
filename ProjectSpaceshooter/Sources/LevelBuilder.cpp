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
	gameSystems.gameData.clearPlayData();
	loadLevelDescribe(gameSystems);
	buildPlayScene(gameSystems, time);
	return nextState(gameSystems);
}

void LevelBuilder::loadLevelDescribe( SystemsSet & gameSystems )
{
	LevelDescription & _levelDescription = gameSystems.gameData.createLevelDescription();
	_levelDescription.ambientColour = Ogre::ColourValue(1.0f,1.0f,1.0f);
	Light * newLight = new Light;
	newLight->position = Vector3(100,100,100);
	_levelDescription.lightsCollections += newLight;

	LevelStage * newStage = new LevelStage;
	newStage->setStageNumber(1);
	newStage->setMissionType(missionType::destroyAllEnemy);


	EnemySpawner * newSpawner = new EnemySpawner(Vector3(2000,0,400),20, 3);
	newSpawner->addEnemyToSpawn(2,8);
	newStage->addSpawner(newSpawner);

	newSpawner = new EnemySpawner(Vector3(-400,0,-4000),10,3);
	newSpawner->addEnemyToSpawn(1,7);
	newSpawner->setSpawnerDelaySinceStageStart(0);
	newStage->addSpawner(newSpawner);

	newSpawner = new EnemySpawner(Vector3(-100,0,4000),10,3);
	newSpawner->addEnemyToSpawn(3,7);
	newSpawner->setSpawnerDelaySinceStageStart(10);
	newStage->addSpawner(newSpawner);

	newSpawner = new EnemySpawner(Vector3(-800,0,1300),30,4);
	newSpawner->addEnemyToSpawn(4,7); 
	newSpawner->setSpawnerDelaySinceStageStart(19);
	newStage->addSpawner(newSpawner);

	newSpawner = new EnemySpawner(Vector3(-1400,0,-1700),20,4);
	newSpawner->addEnemyToSpawn(5,7);
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
	player->setPosition(Vector3(1000,0,0));
	attachCameraToPlayer(gameSystems);
	const WeaponPrefab * weapon = gameSystems.gameData.getWeaponPrefab(2);
	player->addWeapon(weapon);
	weapon = gameSystems.gameData.getWeaponPrefab(3);
	player->addWeapon(weapon);

	StaticObject *stat = mGameData->instantiateStatic(1);
	stat->setPosition(Vector3(3400, 0, 300));
	
	stat = mGameData->instantiateStatic(1);
	stat->setPosition(Vector3(2400, 0, 1800));

	stat = mGameData->instantiateStatic(4);
	stat->setPosition(Vector3(-1400, 0, -3300));

	stat = mGameData->instantiateStatic(3);
	stat->setPosition(Vector3(600, 0, -400));
	stat = mGameData->instantiateStatic(3);
	stat->setPosition(Vector3(-700, 0, 300));
	stat = mGameData->instantiateStatic(3);
	stat->setPosition(Vector3(870, 0, 170));
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
void LevelBuilder::attachCameraToPlayer(SystemsSet & gameSystems)
{
	Ogre::Camera * _camera = gameSystems.gameData.getCameraFor(GAME_STATES::PLAY);
	Player * player = gameSystems.gameData.getPlayer();
	Ogre::SceneNode *cameraNode = player->getCameraNode();
	player->attachCamera(_camera);
}