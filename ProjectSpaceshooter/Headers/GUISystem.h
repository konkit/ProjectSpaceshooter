#pragma once

#include "ogre2d.h"

#include <OgreTextAreaOverlayElement.h>
#include <OgreFontManager.h>

#include "TimeUtility.h"
#include "GameData.h"

#include <sstream>

#define FONT_FOLDER "fonts/"
#define FONT_FILE_NAME "arial.ttf"

#define DOT_WIDTH 0.0075
#define DOT_HEIGHT 0.01
#define CORE_DOT 0.02


class GUISystem	{

public:
	//init - run at start
	void init( Ogre::SceneManager* mSceneMgr);

	//display - run every frame
	void display( GameData& mGameData, TimeData _time );


	~GUISystem();

	


private:
	Ogre2dManager* ogre2dManager;

	//My own overlay play
	Ogre::Overlay* overlay;
	Ogre::OverlayManager* overlayManager;
	Ogre::OverlayContainer* panel;

	Ogre::TextAreaOverlayElement* playerVelocityText;
	Ogre::TextAreaOverlayElement* fpsNumber;

	//load font
	void loadFont(std::string fontFilename);

	//create text area object, attach it to panel and return it (so it can be saved and have the text actualized)
	Ogre::TextAreaOverlayElement* createText(std::string elementID, int posX, int posY );
};
