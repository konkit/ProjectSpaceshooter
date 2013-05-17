#pragma once

#include "GameData.h"
#include "Exceptions.h"


#define SHOW_CURSOR true	//If system cursor should be displayed

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
		wasR_KeyPressed = false;
		wasC_KeyPressed = false;
		was1_KeyPressed = false;
		was2_KeyPressed = false;
		was3_KeyPressed = false;
		was4_KeyPressed = false;
		was5_KeyPressed = false;
		was6_KeyPressed = false;
		was7_KeyPressed = false;
		was8_KeyPressed = false;
		was9_KeyPressed = false;
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
	bool wasR_KeyPressed;
	bool was1_KeyPressed;
	bool was2_KeyPressed;
	bool was3_KeyPressed;
	bool was4_KeyPressed;
	bool was5_KeyPressed;
	bool was6_KeyPressed;
	bool was7_KeyPressed;
	bool was8_KeyPressed;
	bool was9_KeyPressed;
	bool wasC_KeyPressed;
	// Derived WindowEventListener
	// Callback functions run when certain event occurs
	virtual void windowResized(Ogre::RenderWindow* rw);
	virtual void windowClosed(Ogre::RenderWindow* rw);
};
