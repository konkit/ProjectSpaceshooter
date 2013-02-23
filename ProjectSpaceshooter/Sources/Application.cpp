#include "Application.h"

Application::Application() : 
	mRoot(0),
    mPluginsCfg(Ogre::StringUtil::BLANK) 
{}

Application::~Application()
{	
	delete mRoot;
}

bool Application::run()
{
	//Set filenames
#ifdef _DEBUG
    mResourcesCfg = "resources_d.cfg";
#else
    mResourcesCfg = "resources.cfg";
#endif
 
////////////////////////////////////////////
//		Create Ogre::Root object
/////////////////////////////////////////////
    // construct Ogre::Root
	mRoot = OGRE_NEW Ogre::Root();
		mGLPlugin = OGRE_NEW Ogre::GLPlugin();
		mRoot->installPlugin(mGLPlugin);
 
///////////////////////////////////////////
//		Loading Resources from file
///////////////////////////////////////////

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

//////////////////////////////////////////////////////////////
//		Render system (which driver, etc.) and render window
//////////////////////////////////////////////////////////////
	// configure
	// Show the configuration dialog and initialise the system
	if(!(mRoot->restoreConfig() || mRoot->showConfigDialog()))
	{
		return false;
	}

	//Create render window
	mWindow = mRoot->initialise(true, "Project SpaceShooter");

//////////////////////////////////////////////////////////////
//		Initialize resources
//////////////////////////////////////////////////////////////
	// Set default mipmap level (note: some APIs ignore this)
	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
	// initialise all resource groups
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

///////////////////////////////////////////////////////////////
//		Create scene
//////////////////////////////////////////////////////////////
	// Create the SceneManager, in this case a generic one
	mSceneMgr = mRoot->createSceneManager("DefaultSceneManager");

	// Create the camera
	mCamera = mSceneMgr->createCamera("PlayerCam");
		// Position it at 80 in Z direction
		mCamera->setPosition(Ogre::Vector3(0,0,80));
		// Look back along -Z
		mCamera->lookAt(Ogre::Vector3(0,0,-300));
		mCamera->setNearClipDistance(5);
	
	// Create one viewport, entire window
	Ogre::Viewport* vp = mWindow->addViewport(mCamera);
		//Set Background color
		vp->setBackgroundColour(Ogre::ColourValue(0,0,0));
		// Alter the camera aspect ratio to match the viewport
		mCamera->setAspectRatio(
			Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));

/////////////////////////////////////////////////////////////////
//		Setup scene
///////////////////////////////////////////////////////////////////
	Ogre::Entity* ogreHead = mSceneMgr->createEntity("Head", "ogrehead.mesh");
 
	Ogre::SceneNode* headNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	headNode->attachObject(ogreHead);
 
	// Set ambient light
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
 
	// Create a light
	Ogre::Light* l = mSceneMgr->createLight("MainLight");
	l->setPosition(20,80,50);

/////////////////////////////////////////////////////////////////////////
//		Render Loop
//////////////////////////////////////////////////////////////////////////
	while(true)
	{
		// Pump window messages for nice behaviour
		Ogre::WindowEventUtilities::messagePump();
 
		if(mWindow->isClosed())
		{
			return false;
		}
 
		// Render a frame
		if(!mRoot->renderOneFrame()) return false;
	}

	return true;
}
