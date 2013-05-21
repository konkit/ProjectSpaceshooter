#pragma once

#include "ogre2d.h"

#include <OgreTextAreaOverlayElement.h>
#include <OgreFontManager.h>

#include "TimeUtility.h"
#include "GameData.h"

#include <sstream>

#include "GUI_Radar.h"
#include "GUI_MessageConsole.h"

#define FONT_FOLDER "fonts/"
#define FONT_FILE_NAME "arial.ttf"




class PlayGUI	{

public:
	//init - run at start
	void init( Ogre::SceneManager* mSceneMgr)  	{
		//2D graphics
			ogre2dManager = new Ogre2dManager;
			ogre2dManager->init(mSceneMgr, Ogre::RENDER_QUEUE_OVERLAY, true);

		//Radar
			mRadar.init(ogre2dManager);

		//Text Stuff
			//Load Font
			Ogre::FontManager &fontMgr = Ogre::FontManager::getSingleton();
			Ogre::ResourcePtr font = fontMgr.getByName("MyFont");
			font->load();

			//Get overlay object
			Ogre::OverlayManager* overlayManager = & Ogre::OverlayManager::getSingleton();
			overlay = overlayManager->getByName("GUIOverlay");

			//Get text area data to modify it later
			Ogre::OverlayContainer* playerDataPanel = static_cast<Ogre::OverlayContainer*>( overlayManager->getOverlayElement("playerDataPanel") );
			playerData = playerDataPanel->getChild("PlayerDataText");
			
			Ogre::OverlayContainer* messageLogPanel = static_cast<Ogre::OverlayContainer*>( overlayManager->getOverlayElement("messageLogPanel") );
			mMessageConsole = messageLogPanel->getChild("MessageLogText");
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
			mConsole = &mGameData.getMessageConsole();
			std::stringstream messageConsoleString;
				messageConsoleString
					<<"Log :\n"
					<<mConsole->getMessages();
			mMessageConsole->setCaption( messageConsoleString.str() );

		// Show the overlay
			overlay->show();
	}

	void hide()	{
		overlay->hide();
	}


	~PlayGUI()	{
		ogre2dManager->end();
		delete ogre2dManager;
	}

	


private:
	Ogre2dManager* ogre2dManager;

	//overlay object
	Ogre::Overlay* overlay;

	//Texts
	Ogre::OverlayElement* playerData;
	Ogre::OverlayElement* mMessageConsole;

	Radar mRadar;
	MessageConsole* mConsole;
};




