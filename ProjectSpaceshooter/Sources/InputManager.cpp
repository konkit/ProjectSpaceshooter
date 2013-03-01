#include "InputManager.h"




void InputManager::initOIS(Ogre::RenderWindow* window)
{
	mWindow = window;

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
 
    //mRoot->addFrameListener(this);
}


//Adjust mouse clipping area
void InputManager::windowResized(Ogre::RenderWindow* rw)
{
    unsigned int width, height, depth;
    int left, top;
    rw->getMetrics(width, height, depth, left, top);
 
    const OIS::MouseState &ms = mMouse->getMouseState();
    ms.width = width;
    ms.height = height;
}
 
//Unattach OIS before window shutdown (very important under Linux)
void InputManager::windowClosed(Ogre::RenderWindow* rw)
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

bool InputManager::updateInput(GameData& mGameData)
{
	// Pump window messages for nice behaviour
	Ogre::WindowEventUtilities::messagePump();

	if(mWindow->isClosed())
	{
		return false;
	}

	if(mWindow->isClosed())
		return false;
 
	//Need to capture/update each device
	mKeyboard->capture();
	mMouse->capture();

	float tmpX=0.0, tmpY=0.0, tmpZ=0.0;

	 
    if(mKeyboard->isKeyDown(OIS::KC_ESCAPE))
        return false;

	if(mKeyboard->isKeyDown(OIS::KC_W) )
	{
		tmpZ += 0.05;
	}

	if(mKeyboard->isKeyDown(OIS::KC_S) )
	{
		tmpZ -= 0.05;
	}

	if(mKeyboard->isKeyDown(OIS::KC_A) )
	{
		tmpX += 0.05;
	}

	if(mKeyboard->isKeyDown(OIS::KC_D) )
	{
		tmpX -= 0.05;
	}

	mGameData.getPlayer()->getPhysicsComponent().setVelocity(tmpX, tmpY, tmpZ);

	return true;
}