#pragma once

#include "stdafx.h"
#include "GameData.h"
#include "GameObject.h"
#include "GameObjectFactory.h"

GameData::GameData(void)
{
	mBulletCollection = new GameObjectsCollection(GameObjectType::bulletObject);
	mStaticCollection = new GameObjectsCollection(GameObjectType::staticObject);
	mEnemyCollection = new GameObjectsCollection(GameObjectType::enemyObject);
	mPlayer = GameObjectFactory::getGameObject(GameObjectType::player);

	camX = 0.0;
	camY = 0.0;
	camZ = 0.0;
}


GameData::~GameData(void)
{
}

//Tymczasowo to jest tutaj by ustawic jak¹kolwiek scenê
void GameData::initScene(Ogre::Root* mRoot, Ogre::RenderWindow* mWindow)
{
	// Create the SceneManager, in this case a generic one
	mSceneMgr = mRoot->createSceneManager("DefaultSceneManager");

	// Create the camera
	mCamera = mSceneMgr->createCamera("PlayerCam");
		// Position it at 80 in Z direction
		mCamera->setPosition(Ogre::Vector3(0.0, 350.0, -100.0));
		// Look back along -Z
		mCamera->lookAt(0.0, 1.0, 1.0);
		mCamera->setNearClipDistance(5);

	//skyplane
	Ogre::Plane plane;
		plane.d = 2500;
		plane.normal = Ogre::Vector3::UNIT_Y;
	mSceneMgr->setSkyPlane(true, plane, "Examples/SpaceSkyPlane", 1000, 45);
	
	// Create one viewport, entire window
	Ogre::Viewport* vp = mWindow->addViewport(mCamera);
		//Set Background color
		vp->setBackgroundColour(Ogre::ColourValue(0,0,0));
		// Alter the camera aspect ratio to match the viewport
		mCamera->setAspectRatio(
			Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
}


void GameData::setScene()
{
	Ogre::Entity* ogreHead = mSceneMgr->createEntity("Head", "smallfighter.MESH");
 
	shipNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	shipNode->attachObject(ogreHead);
	shipNode->setPosition(Ogre::Vector3(camX, camY, camZ));
 
	// Set ambient light
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
 
	// Create a light
	Ogre::Light* l = mSceneMgr->createLight("MainLight");
	l->setPosition(-50,50,0);
	l->setPowerScale(200.0);
}


void GameData::updateScene()
{
	shipNode->setPosition(Ogre::Vector3(camX, camY, camZ));

	//std::cout<<"Spaceship position - "<<camX<<", "<<camY<<", "<<camZ<<"\n";
}