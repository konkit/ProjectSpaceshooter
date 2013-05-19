#pragma once

#include "ogre2d.h"

#include <OgreTextAreaOverlayElement.h>
#include <OgreFontManager.h>

#include "TimeUtility.h"
#include "GameData.h"

#include <sstream>

#include "GUI_Radar.h"
#include "MessageConsole.h"

#define FONT_FOLDER "fonts/"
#define FONT_FILE_NAME "arial.ttf"




class GUISystem	{

public:
	//init - run at start
	void init( Ogre::SceneManager* mSceneMgr)  	{
		//2D graphics
			ogre2dManager = new Ogre2dManager;
			ogre2dManager->init(mSceneMgr, Ogre::RENDER_QUEUE_OVERLAY, true);

		//Radar
			mRadar.init(ogre2dManager);

		//Text Stuff
			loadFont("arial.ttf");

			// get the resource manager
			overlayManager = & Ogre::OverlayManager::getSingleton();

			// Create a player data panel
			playerDataPanel = static_cast<Ogre::OverlayContainer*>(
				overlayManager->createOverlayElement("Panel", "PanelName1"));
			playerDataPanel->setMetricsMode(Ogre::GMM_PIXELS);
			playerDataPanel->setPosition(10, 20);
			playerDataPanel->setDimensions(200, 120);
			playerDataPanel->setMaterialName( "grayBackground" );

			// Create a message log panel
			messageLogPanel = static_cast<Ogre::OverlayContainer*>(
				overlayManager->createOverlayElement("Panel", "PanelName2"));
			messageLogPanel->setMetricsMode(Ogre::GMM_PIXELS);
			messageLogPanel->setPosition(10, 200);
			messageLogPanel->setDimensions(200, 120);
			messageLogPanel->setMaterialName( "grayBackground" );

			// Create an overlay, and add the panel
			overlay = overlayManager->create("OverlayName");
			overlay->add2D(playerDataPanel);
			overlay->add2D(messageLogPanel);



			//create text areas
			playerData = createText(playerDataPanel, "playerVelocity1", 0, 5 );
			mMessageConsole =  createText(messageLogPanel, "messageLog1", 0, 5 );
		//END text stuff
	}

	//display - run every frame
	void display( GameData& mGameData, TimeData _time ){

		//Radar
		mRadar.display(mGameData, _time);			

		//Text stuff

		//display player velocity as text (actualize text contents)
		std::stringstream playerDataString;
			playerDataString
				<<"Velocity : "<<mGameData.getPlayer()->getPhysicsComponent().getCurrentVelocityMagnitude()
				<<"\nTarget velocity : "<<mGameData.getPlayer()->getPhysicsComponent().getTargetVelocityValue()
				<<"\nHealth : "<<mGameData.getPlayer()->getHealthValue()<<" / "<<mGameData.getPlayer()->getMaxHealthValue()
				<<"\n"
				<<"\nFPS : "<<_time.currentFPSValue;
		playerData->setCaption( playerDataString.str() );

		//draw message console
		std::stringstream messageConsoleString;
			messageConsoleString
				<<"Log :\n"
				<<mConsole.getMessages();
		mMessageConsole->setCaption( messageConsoleString.str() );

		// Show the overlay
		overlay->show();
	}


	~GUISystem()	{
		ogre2dManager->end();
		delete ogre2dManager;
	}

	


private:
	Ogre2dManager* ogre2dManager;

	//My own overlay play
	Ogre::Overlay* overlay;
	Ogre::OverlayManager* overlayManager;

	//Panels
	Ogre::OverlayContainer* playerDataPanel;
	Ogre::OverlayContainer* messageLogPanel;

	Ogre::TextAreaOverlayElement* playerData;
	Ogre::TextAreaOverlayElement* mMessageConsole;

	Radar mRadar;
	MessageConsole mConsole;

	//load font
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

	//create text area object, attach it to panel and return it (so it can be saved and have the text actualized)
	Ogre::TextAreaOverlayElement* createText(Ogre::OverlayContainer* panel, std::string elementID, int posX, int posY )	{
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
};




