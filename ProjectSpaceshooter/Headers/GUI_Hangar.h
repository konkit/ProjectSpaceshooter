#pragma once

#include "GUI_AbstractInstance.h"

// GUI displayed during game over state
// while it just displays text, it doesnt do much more than parent gui class
class HangarGUI : public AbstractInstanceGUI
{
public:
	//init - run at start
	void init( Ogre::SceneManager* mSceneMgr)  	{
		AbstractInstanceGUI::init("HangarGUI");
	}

	//rest is in parent class
};