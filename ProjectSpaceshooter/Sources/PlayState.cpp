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
	mSceneMgr->setSkyPlane(true, plane, "Examples/SpaceSkyPlane", 1000, 45);

	//create sceneNode for player
	mGame->getGameData()->shipNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	//atach model to that node
	mGame->getGameData()->shipNode->attachObject(ogreHead);
	//save node in player's GraphicsComponent
	mGame->getGameData()->getPlayer()->getGraphicsComponent().initNode(mGame->getGameData()->shipNode);

	// Set ambient light
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));

	// Create a light
	Ogre::Light* light = mSceneMgr->createLight("MainLight");
	light->setPosition(-50,50,0);
	light->setPowerScale(200.0);
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
	mCamera->setPosition(Ogre::Vector3(0.0,350.0,-100.0));
	mCamera->lookAt(Ogre::Vector3(0,1.0,1.0));
	// set the near clip distance
	mCamera->setNearClipDistance(5);
}

