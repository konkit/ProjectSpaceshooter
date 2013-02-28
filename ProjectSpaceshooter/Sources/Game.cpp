#include "Game.h"




bool Game::run()
{ 
	initOgre();

	mInputManager.initOIS( getWindowHandle() );

	initScene();
	setScene();

	while(true)
	{
		if(mInputManager.updateInput(camX, camY, camZ)==false)
			return false;

		mCamera->setPosition(Ogre::Vector3(camX, camY, camZ));


		// Render a frame
		if(! getRoot()->renderOneFrame()) return false;
	}

	return true;
}





void Game::initScene()
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

void Game::setScene()
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



void Game::initOgre()
{
	// Create OgreRoot
	mRoot = OGRE_NEW Ogre::Root();

	// install openGL plugin
	mGLPlugin = OGRE_NEW Ogre::GLPlugin();
	mRoot->installPlugin(mGLPlugin);

	// Load config file and init window
	mRoot->restoreConfig();

	// Create render window
	mWindow = mRoot->initialise(true, "Project SpaceShooter");
	
	//Set filenames
	#ifdef _DEBUG
		Ogre::String mResourcesCfg = "resources_d.cfg";
	#else
		Ogre::String mResourcesCfg = "resources.cfg";
	#endif

	// set up resources
	// Load resource paths from config file
	Ogre::ConfigFile cf;
	cf.load(mResourcesCfg);
	
	// Go through all sections & settings in the file
	Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
 
	Ogre::String secName, typeName, archName;
	while (seci.hasMoreElements())
	{
		secName = seci.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator i;
		for (i = settings->begin(); i != settings->end(); ++i)
		{
			typeName = i->first;
			archName = i->second;
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
				archName, typeName, secName);
		}
	}

	// Set default mipmap level (note: some APIs ignore this)
	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
	// initialise all resource groups
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}
