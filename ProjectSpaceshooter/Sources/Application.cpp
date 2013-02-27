#include "Application.h"

Application::Application() : 
	mRoot(0)
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

//////////////////////////////////////////////////////////////
//		Initialize input system and register addFrameListener
//////////////////////////////////////////////////////////////
	initOIS();

///////////////////////////////////////////////////////////////
//		Create scene
//////////////////////////////////////////////////////////////
	initScene();

/////////////////////////////////////////////////////////////////
//		Setup scene
///////////////////////////////////////////////////////////////////
	setScene();

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

//Function which is running every frame
//Derieved from FrameListener class
//It is being run from mRoot->renderOneFrame()
bool Application::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    if(mWindow->isClosed())
        return false;
 
    //Need to capture/update each device
    mKeyboard->capture();
    mMouse->capture();

	if(updateInput(evt)==false)
		return false;

	mCamera->setPosition(Ogre::Vector3(camX, camY, camZ));

 
	return true;
}

void Application::initScene()
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

void Application::setScene()
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


//Adjust mouse clipping area
void Application::windowResized(Ogre::RenderWindow* rw)
{
    unsigned int width, height, depth;
    int left, top;
    rw->getMetrics(width, height, depth, left, top);
 
    const OIS::MouseState &ms = mMouse->getMouseState();
    ms.width = width;
    ms.height = height;
}
 
//Unattach OIS before window shutdown (very important under Linux)
void Application::windowClosed(Ogre::RenderWindow* rw)
{
    //Only close for window that created OIS (the main window in these demos)
    if( rw == mWindow )
    {
        if( mInputManager )
        {
            mInputManager->destroyInputObject( mMouse );
            mInputManager->destroyInputObject( mKeyboard );
 
            OIS::InputManager::destroyInputSystem(mInputManager);
            mInputManager = 0;
        }
    }
}


void Application::initOIS()
{
	Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
    OIS::ParamList pl;
    size_t windowHnd = 0;
    std::ostringstream windowHndStr;
 
    mWindow->getCustomAttribute("WINDOW", &windowHnd);
    windowHndStr << windowHnd;
    pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
 
    mInputManager = OIS::InputManager::createInputSystem( pl );
 
    mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject( OIS::OISKeyboard, false ));
    mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject( OIS::OISMouse, false ));
 
    //Set initial mouse clipping size
    windowResized(mWindow);
 
    //Register as a Window listener
    Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);
 
    mRoot->addFrameListener(this);
}

 

bool Application::updateInput(const Ogre::FrameEvent& evt)
{
	 
    if(mKeyboard->isKeyDown(OIS::KC_ESCAPE))
        return false;

	if(mKeyboard->isKeyDown(OIS::KC_W) )
	{
		camZ += 10 * evt.timeSinceLastFrame;
	}

	if(mKeyboard->isKeyDown(OIS::KC_S) )
	{
		camZ -= 10 * evt.timeSinceLastFrame;
	}

	if(mKeyboard->isKeyDown(OIS::KC_A) )
	{
		camX += 10 * evt.timeSinceLastFrame;
	}

	if(mKeyboard->isKeyDown(OIS::KC_D) )
	{
		camX -= 10 * evt.timeSinceLastFrame;
	}

	return true;
}