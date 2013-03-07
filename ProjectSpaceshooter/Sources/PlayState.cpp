#include "GameState.h"

PlayState::PlayState( Game * game )
	:GameState(game)
{
	mSceneMgr = game->getOgreManager()->getRoot()->createSceneManager(Ogre::ST_GENERIC, "primary");
	createCamera();

	Ogre::Entity* ogreHead = mSceneMgr->createEntity("Head", "smallfighter.MESH");
	Ogre::Plane plane;
		plane.d = 2500;
		plane.normal = Ogre::Vector3::UNIT_Y;
	//mSceneMgr->setSkyPlane(true, plane, "Examples/SpaceSkyPlane", 1000, 45);
	mSceneMgr->setSkyBox(true, "Examples/SpaceSkyBox");

	//create sceneNode for player
	mGame->getGameData()->shipNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();

	//atach model to that node
	mGame->getGameData()->shipNode->attachObject(ogreHead);
	Ogre::SceneNode *cameraNode = mGame->getGameData()->shipNode->createChildSceneNode();
		cameraNode->attachObject(mCamera);
		cameraNode->setPosition(Ogre::Vector3(0.0,20.0,-60.0));
	mCamera->lookAt(Ogre::Vector3(0,0,100));

	//bullet model
	mGame->getGameData()->bulletEntity = mSceneMgr->createEntity("BulletEntity", "bullet2.MESH");

	//save node in player's GraphicsComponent
	mGame->getGameData()->getPlayer()->getGraphicsComponent().initNode(mGame->getGameData()->shipNode);
	Ogre::Entity* ship = mSceneMgr->createEntity("Staic", "smallfighter.MESH");
	Ogre::SceneNode *stat = mSceneMgr->getRootSceneNode()->createChildSceneNode();
		//stat->attachObject(ship);
		stat->attachObject(mGame->getGameData()->bulletEntity);
		stat->setPosition(Ogre::Vector3(70,0,100));
		//stat->pitch(Ogre::Degree(-90));
		stat->scale(3,3,3);


	// Set ambient light
	mSceneMgr->setAmbientLight(Ogre::ColourValue(1.0, 1.0, 1.0));

	// Create a light
	Ogre::Light* light = mSceneMgr->createLight("MainLight");
	light->setPosition(-50,50,0);
	light->setPowerScale(200.0);
	//Ogre::Light* spotLight = mSceneMgr->createLight("AdditionalLight");
	//adLight->setPosition(50,50,-200);
	//adLight->setPowerScale(400.0);
}

bool PlayState::update()
{
	if(mGame->getGameData()->changeFlag)
		mGame->changeState(mGame->getPause());
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

