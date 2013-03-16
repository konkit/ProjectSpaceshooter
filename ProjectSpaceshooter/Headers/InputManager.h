#pragma once

#include "GameData.h"
#include "Exceptions.h"




/** Class reading input from system and acting appropriately on GameData
  *
  * @author 
  */
class InputManager : public Ogre::WindowEventListener
{
public:
	InputManager() 
	{ 
		wasP_KeyPressed = false;
		wasH_KeyPressed = false;
	}
	//initialize OIS 
	void initOIS(Ogre::RenderWindow* window);
	
	//update data (temporarily just camera coords)
	void updateInputForGame(GameData& mGameData, float deltaTime, unsigned long currentTime);
	void updateInputForPause(GameData& mGameData);

private:
	// OIS Input devices
	OIS::InputManager* mInputManager;
	OIS::Mouse*    mMouse;
	OIS::Keyboard* mKeyboard;
	Ogre::RenderWindow* mWindow;
	bool wasP_KeyPressed;
	bool wasH_KeyPressed;
	// Derived WindowEventListener
	// Callback functions run when certain event occurs
	virtual void windowResized(Ogre::RenderWindow* rw);
	virtual void windowClosed(Ogre::RenderWindow* rw);
};

