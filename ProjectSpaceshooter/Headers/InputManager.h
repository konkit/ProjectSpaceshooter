#pragma once

#include "GameData.h"


//Class reading input from system and acting appropriately on GameData
class InputManager : public Ogre::WindowEventListener
{
public:
	//initialize OIS 
	void initOIS(Ogre::RenderWindow* window);
	
	//update data (temporairly just camera coords)
	bool updateInput(GameData& mGameData);

private:
	// OIS Input devices
	OIS::InputManager* mInputManager;
	OIS::Mouse*    mMouse;
	OIS::Keyboard* mKeyboard;

	Ogre::RenderWindow* mWindow;

	// Derived WindowEventListener
	// Callback functions run when certain event occurs
    virtual void windowResized(Ogre::RenderWindow* rw);
    virtual void windowClosed(Ogre::RenderWindow* rw);
};

