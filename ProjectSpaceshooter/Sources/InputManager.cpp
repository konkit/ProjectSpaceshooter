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

bool InputManager::updateInput(GameData& mGameData, float deltaTime)
{
	static unsigned long lastTime = 0; 
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

	//temporary values
	Ogre::Vector3 tmpPos(0.0, 0.0, 0.0);
	float tmpAngle=0.0;

	 
    if(mKeyboard->isKeyDown(OIS::KC_ESCAPE))
        return false;

	if(mKeyboard->isKeyDown(OIS::KC_W) )
	{
		tmpPos.z += 1.0;
	}

	if(mKeyboard->isKeyDown(OIS::KC_S) )
	{
		tmpPos.z -= 1.0;
	}

	if(mKeyboard->isKeyDown(OIS::KC_Q) )
	{
		tmpPos.x += 1.0;
	}
	
	if(mKeyboard->isKeyDown(OIS::KC_E) )
	{
		tmpPos.x -= 1.0;
	}
	if(mKeyboard->isKeyDown(OIS::KC_A) )
	{
		tmpAngle += 1.0;
	}
	if(mKeyboard->isKeyDown(OIS::KC_D) )
	{
		tmpAngle -= 1.0;
	}

	if(mKeyboard->isKeyDown(OIS::KC_SPACE) )
	{
		//set shoot on player
	}

	//unsigned long deltaTime = mTime.getMilliseconds() - lastTime;
	static float cntTimeElapsed = 0.0;
	cntTimeElapsed += deltaTime;

	if (mKeyboard->isKeyDown(OIS::KC_P) && ( cntTimeElapsed > 1000))
	{
		mGameData.changeFlag = !mGameData.changeFlag;
		cntTimeElapsed = 0.0;
		//lastTime = mTime.getMilliseconds();
	}

	mGameData.getPlayer()->getPhysicsComponent().setVelocity(tmpPos);
	mGameData.getPlayer()->getPhysicsComponent().setRotVelocity(tmpAngle);

	return true;
}