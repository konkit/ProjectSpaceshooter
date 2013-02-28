#ifndef __SPACESHOOTER_GAME_DATA__
#define __SPACESHOOTER_GAME_DATA__




//Class which stores gameobjects and all data required by systems to do their job
class GameData
{
public:
	
	//Tymczasowo to jest tutaj by ustawic jak¹kolwiek scenê
	//Dlatego nie jest to w cpp
	void initScene(Ogre::Root* mRoot, Ogre::RenderWindow* mWindow)
	{
		// Create the SceneManager, in this case a generic one
		mSceneMgr = mRoot->createSceneManager("DefaultSceneManager");

		// Create the camera
		mCamera = mSceneMgr->createCamera("PlayerCam");
			// Position it at 80 in Z direction
			mCamera->setPosition(Ogre::Vector3(0,15,-50));
			// Look back along -Z
			mCamera->lookAt(Ogre::Vector3(0,5,0));
			mCamera->setNearClipDistance(5);

			camX = 0;
			camY = 15;
			camZ = -50;
	
		// Create one viewport, entire window
		Ogre::Viewport* vp = mWindow->addViewport(mCamera);
			//Set Background color
			vp->setBackgroundColour(Ogre::ColourValue(0,0,0));
			// Alter the camera aspect ratio to match the viewport
			mCamera->setAspectRatio(
				Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
	}


	void setScene()
	{
		Ogre::Entity* ogreHead = mSceneMgr->createEntity("Head", "smallfighter.MESH");
 
		Ogre::SceneNode* headNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
		headNode->attachObject(ogreHead);
 
		// Set ambient light
		mSceneMgr->setAmbientLight(Ogre::ColourValue(0.7, 0.7, 0.7));
 
		// Create a light
		Ogre::Light* l = mSceneMgr->createLight("MainLight");
		l->setPosition(20,80,50);
	}



		Ogre::Camera* mCamera;
		float camX, camY, camZ;
private:
	//All GameObjects
	Ogre::SceneManager* mSceneMgr;


};

#endif