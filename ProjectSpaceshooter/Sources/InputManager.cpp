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

		if( SHOW_CURSOR == true )	{
			pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND" )));
			pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));
		}
 
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

void InputManager::updateInputForGame(GameData& mGameData, float deltaTime, unsigned long currentTime)
{
	static unsigned long lastTime = 0; 
	// Pump window messages for nice behaviour
	Ogre::WindowEventUtilities::messagePump();
	
	if(mWindow->isClosed())
	{
		throw WindowClosedException();
	}
 
	//Need to capture/update each device
	mKeyboard->capture();
	mMouse->capture();

	//temporary values
	Ogre::Vector3 tmpPos(0.0, 0.0, 0.0);
	float tmpAngle=0.0;

	 
    if(mKeyboard->isKeyDown(OIS::KC_ESCAPE))
		throw WindowClosedException();

	bool forward = false, 
		backward = false, 
		left = false, 
		right = false, 
		clockwise = false, 
		cntclockwise = false;

	if(mKeyboard->isKeyDown(OIS::KC_W) )	{
		//tmpPos.z += 1.0;
		forward = true;
	}
	
	if(mKeyboard->isKeyDown(OIS::KC_S) )	{
		//tmpPos.z -= 1.0;
		backward = true;
	}

	if(mKeyboard->isKeyDown(OIS::KC_Q) )	{
		//tmpPos.x += 1.0;
		left = true;
	}
	
	if(mKeyboard->isKeyDown(OIS::KC_E) )	{
		//tmpPos.x -= 1.0;
		right = true;
	}
	if(mKeyboard->isKeyDown(OIS::KC_A) )	{
		//tmpAngle += 1.0;
		cntclockwise = true;
	}
	if(mKeyboard->isKeyDown(OIS::KC_D) )	{
		//tmpAngle -= 1.0;
		clockwise = true;
	}

	mGameData.getPlayer()->setMovement(forward, backward, left, right);
	mGameData.getPlayer()->getPhysicsComponent().setRotation(clockwise, cntclockwise);

	if(mKeyboard->isKeyDown(OIS::KC_SPACE) )	{
		//set shoot on player
		mGameData.getPlayer()->setShoot(currentTime);
	}

	if( mKeyboard->isKeyDown(OIS::KC_H) )	{
		mGameData.getPlayer()->addRecoilVectorToCurrentVelocity( Ogre::Vector3(-25.0, 0.0 ,0.0));
	}


	if (!mKeyboard->isKeyDown(OIS::KC_P) && (wasP_KeyPressed))	{
		mGameData.setChangeToPause(true);
		wasP_KeyPressed = false;
	} else if (mKeyboard->isKeyDown(OIS::KC_P))	{
		wasP_KeyPressed = true;
	}

	if (!mKeyboard->isKeyDown(OIS::KC_H) && (wasH_KeyPressed))	{
		mGameData.setChangeToHangar(true);
		wasH_KeyPressed = false;
	} else if (mKeyboard->isKeyDown(OIS::KC_H))	{
		wasH_KeyPressed = true;
	}

	Player * player = mGameData.getPlayer();
	if (!mKeyboard->isKeyDown(OIS::KC_1) && (was1_KeyPressed))	{
		player->changeWeaponTo(1);
		was1_KeyPressed = false;
	} else if (mKeyboard->isKeyDown(OIS::KC_1))	{
		was1_KeyPressed = true;
	}
	if (!mKeyboard->isKeyDown(OIS::KC_2) && (was2_KeyPressed))	{
		player->changeWeaponTo(2);
		was2_KeyPressed = false;
	} else if (mKeyboard->isKeyDown(OIS::KC_2))	{
		was2_KeyPressed = true;
	}
	if (!mKeyboard->isKeyDown(OIS::KC_3) && (was3_KeyPressed))	{
		player->changeWeaponTo(3);
		was3_KeyPressed = false;
	} else if (mKeyboard->isKeyDown(OIS::KC_3))	{
		was3_KeyPressed = true;
	}
	if (!mKeyboard->isKeyDown(OIS::KC_4) && (was4_KeyPressed))	{
		player->changeWeaponTo(4);
		was4_KeyPressed = false;
	} else if (mKeyboard->isKeyDown(OIS::KC_4))	{
		was4_KeyPressed = true;
	}
	if (!mKeyboard->isKeyDown(OIS::KC_5) && (was5_KeyPressed))	{
		player->changeWeaponTo(5);
		was5_KeyPressed = false;
	} else if (mKeyboard->isKeyDown(OIS::KC_5))	{
		was5_KeyPressed = true;
	}
	if (!mKeyboard->isKeyDown(OIS::KC_6) && (was6_KeyPressed))	{
		player->changeWeaponTo(6);
		was6_KeyPressed = false;
	} else if (mKeyboard->isKeyDown(OIS::KC_6))	{
		was6_KeyPressed = true;
	}
	if (!mKeyboard->isKeyDown(OIS::KC_7) && (was7_KeyPressed))	{
		player->changeWeaponTo(7);
		was7_KeyPressed = false;
	} else if (mKeyboard->isKeyDown(OIS::KC_7))	{
		was7_KeyPressed = true;
	}
	if (!mKeyboard->isKeyDown(OIS::KC_8) && (was8_KeyPressed))	{
		player->changeWeaponTo(8);
		was8_KeyPressed = false;
	} else if (mKeyboard->isKeyDown(OIS::KC_8))	{
		was8_KeyPressed = true;
	}
	if (!mKeyboard->isKeyDown(OIS::KC_9) && (was9_KeyPressed))	{
		player->changeWeaponTo(9);
		was9_KeyPressed = false;
	} else if (mKeyboard->isKeyDown(OIS::KC_9))	{
		was9_KeyPressed = true;
	}
	//mGameData.getPlayer()->setTargetVelocity( tmpPos );
	//mGameData.getPlayer()->getPhysicsComponent().setRotVelocity(tmpAngle);
}

void InputManager::updateInputForPause( GameData& mGameData )
{
	// Pump window messages for nice behavior
	Ogre::WindowEventUtilities::messagePump();

	if(mWindow->isClosed())
	{
		throw WindowClosedException();
	}

	mKeyboard->capture();
	mMouse->capture();
		
	if(mKeyboard->isKeyDown(OIS::KC_ESCAPE))
		throw WindowClosedException();

	if(mKeyboard->isKeyDown(OIS::KC_Q) )
		throw WindowClosedException();

	if (!mKeyboard->isKeyDown(OIS::KC_P) && (wasP_KeyPressed))
	{
		mGameData.setChangeToPlay(true);
		wasP_KeyPressed = false;
	} else if (mKeyboard->isKeyDown(OIS::KC_P))
	{
		wasP_KeyPressed = true;
	}

	if (!mKeyboard->isKeyDown(OIS::KC_R) && (wasR_KeyPressed))
	{
		mGameData.setChangeToPlay(true);
		wasR_KeyPressed = false;
	} else if (mKeyboard->isKeyDown(OIS::KC_R))
	{
		wasR_KeyPressed = true;
	}
}
