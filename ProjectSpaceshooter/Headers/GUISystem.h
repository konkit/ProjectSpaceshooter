#pragma once

#include "ogre2d.h"

class GUISystem	{

public:
	void init( Ogre::SceneManager* mSceneMgr)  	{
		ogre2dManager = new Ogre2dManager;
		ogre2dManager->init(mSceneMgr, Ogre::RENDER_QUEUE_OVERLAY, true);

		//Ogre::TextureManager::getSingleton().load("Image.jpg",Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	}

	void display(){
		//ogre2dManager->spriteBltFull("Image.jpg", -0.5, 0.5, 0.5, -0.5);
	}


	~GUISystem()	{
		//Ogre::TextureManager::getSingleton().unload("Image.jpg");

		ogre2dManager->end();
		delete ogre2dManager;
	}

private:
	Ogre2dManager* ogre2dManager;

};
