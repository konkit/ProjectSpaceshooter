#pragma once

#include "ogre2d.h"

#include <OgreTextAreaOverlayElement.h>
#include <OgreFontManager.h>

#include "TimeUtility.h"
#include "GameData.h"

#include <sstream>

#define FONT_FOLDER "fonts/"
#define FONT_FILE_NAME "arial.ttf"


class GUISystem	{

public:
	


	void init( Ogre::SceneManager* mSceneMgr)  	{
		ogre2dManager = new Ogre2dManager;
		ogre2dManager->init(mSceneMgr, Ogre::RENDER_QUEUE_OVERLAY, true);

		//This function loads image (in example from folder media/materials/textures/ )
		Ogre::TextureManager::getSingleton().load("radar_background.png",Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

		//My own overlay play
			loadFont("arial.ttf");

			// get the resource manager
			overlayManager = & Ogre::OverlayManager::getSingleton();

			// Create a panel
			panel = static_cast<Ogre::OverlayContainer*>(
				overlayManager->createOverlayElement("Panel", "PanelName"));
			panel->setMetricsMode(Ogre::GMM_PIXELS);
			panel->setPosition(10, 20);
			panel->setDimensions(200, 100);
			panel->setMaterialName( "grayBackground" );

			// Create an overlay, and add the panel
			overlay = overlayManager->create("OverlayName");
			overlay->add2D(panel);

			//create text areas
			playerVelocityText = createText( "playerVelocity1", 0, 25 );
			fpsNumber = createText( "fps1", 0, 5);
	}

	void display( GameData& mGameData, TimeData _time ){
		//This function displays this texture
		ogre2dManager->spriteBltFull("radar_background.png", 0.6, 1.0, 1.0, 0.5);

		std::stringstream playerVelocityString;
			playerVelocityString<<"Velocity : "<<mGameData.getPlayer()->getPhysicsComponent().getCurrentVelocity();

		playerVelocityText->setCaption( playerVelocityString.str() );

		std::stringstream fpsString;
			fpsString<<"FPS : "<<_time.currentFPSValue;

		fpsNumber->setCaption( fpsString.str() );

		// Show the overlay
		overlay->show();
	}


	~GUISystem()	{
		//This function unloads previously loaded texture
		Ogre::TextureManager::getSingleton().unload("radar_background.png");

		ogre2dManager->end();
		delete ogre2dManager;
	}

	void loadFont(std::string fontFilename)	{
		Ogre::ResourceGroupManager &resGroupMgr = Ogre::ResourceGroupManager::getSingleton();
			// tell it to look at this location
			resGroupMgr.addResourceLocation(FONT_FOLDER, "FileSystem");
			// get the font manager
			Ogre::FontManager &fontMgr = Ogre::FontManager::getSingleton();
			// create a font resource
			Ogre::ResourcePtr font = fontMgr.create("MyFont", "General");
			// set as truetype
			font->setParameter("type", "truetype");
			// set the .ttf file name
			font->setParameter("source", fontFilename);
			// set the size
			font->setParameter("size", "26");
			// set the dpi
			font->setParameter("resolution", "96");
			// load the ttf
			font->load();
	}

	Ogre::TextAreaOverlayElement* createText(std::string elementID, int posX, int posY )	{
		// Create a text area
		Ogre::TextAreaOverlayElement* textArea = static_cast<Ogre::TextAreaOverlayElement*>(
			overlayManager->createOverlayElement("TextArea", elementID));
		textArea->setMetricsMode(Ogre::GMM_PIXELS);
		textArea->setPosition(posX, posY);
		textArea->setDimensions(100, 20);
		textArea->setCharHeight(16);
		textArea->setFontName("MyFont");
		textArea->setColourBottom(Ogre::ColourValue(0.3, 0.5, 0.3));
		textArea->setColourTop(Ogre::ColourValue(0.5, 0.7, 0.5));
 
		// Add the text area to the panel
		panel->addChild(textArea);

		return textArea;
	}


private:
	Ogre2dManager* ogre2dManager;

	//My own overlay play
	Ogre::Overlay* overlay;
	Ogre::OverlayManager* overlayManager;
	Ogre::OverlayContainer* panel;

	Ogre::TextAreaOverlayElement* playerVelocityText;
	Ogre::TextAreaOverlayElement* fpsNumber;
};
