#pragma once

#include "ogre2d.h"

class GUISystem	{

public:
	void init( Ogre::SceneManager* mSceneMgr)  	{
		ogre2dManager = new Ogre2dManager;
		ogre2dManager->init(mSceneMgr, Ogre::RENDER_QUEUE_OVERLAY, true);

		//This function loads image (in example from folder media/materials/textures/ )
		//Ogre::TextureManager::getSingleton().load("Image.jpg",Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	}

	void display(){
		//This function displays this texture
		//ogre2dManager->spriteBltFull("Image.jpg", -0.5, 0.5, 0.5, -0.5);
	}


	~GUISystem()	{
		//This function unloads previously loaded texture
		//Ogre::TextureManager::getSingleton().unload("Image.jpg");

		ogre2dManager->end();
		delete ogre2dManager;
	}

private:
	Ogre2dManager* ogre2dManager;

};
