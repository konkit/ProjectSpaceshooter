#pragma once

#include "GUI_AbstractInstance.h"

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



// Play state GUI class
// 
class PlayGUI : public 	AbstractInstanceGUI
{

public:
	//init - run at start
	void init( Ogre::SceneManager* mSceneMgr)  	{
		AbstractInstanceGUI::init("GUIOverlay");

		//2D graphics
			ogre2dManager = new Ogre2dManager;
			ogre2dManager->init(mSceneMgr, Ogre::RENDER_QUEUE_OVERLAY, true);

		//Radar
			mRadar.init(ogre2dManager);

		//Text Stuff
			//Get text area data to modify it later
			Ogre::OverlayContainer* playerDataPanel = static_cast<Ogre::OverlayContainer*>( overlayManager->getOverlayElement("playerDataPanel") );
			playerData = playerDataPanel->getChild("PlayerDataText");
			
			Ogre::OverlayContainer* messageLogPanel = static_cast<Ogre::OverlayContainer*>( overlayManager->getOverlayElement("messageLogPanel") );
			mMessageConsole = messageLogPanel->getChild("MessageLogText");
	}

	//display - run every frame
	void display( GameData& mGameData, TimeData _time ){
		//Radar
			//Draw radar
			mRadar.display(mGameData, _time);			

		//Text stuff
			//Some references to speed up everything
			Player& playerRef = *(mGameData.getPlayer());

			//Set text of player data textArea
			std::stringstream playerDataString;
				playerDataString
					<<"Velocity : "<<playerRef.getPhysicsComponent().getCurrentVelocityMagnitude()
					<<"\nTarget velocity : "<<playerRef.getPhysicsComponent().getTargetVelocityValue()
					<<"\nHealth : "<<playerRef.getHealthValue()<<" / "<<playerRef.getMaxHealthValue()
					<<"\nCore Health : "<<mGameData.getCore().getHealthValue()
					<<"\nScore : "<<playerRef.getScore()
					<<"\n"
					<<"\nFPS : "<<_time.currentFPSValue;
			playerData->setCaption( playerDataString.str() );

			//set text of message console textArea
			mConsole = &mGameData.getMessageConsole();
			std::stringstream messageConsoleString;
				messageConsoleString
					<<"Log :\n"
					<<mConsole->getMessages();
			mMessageConsole->setCaption( messageConsoleString.str() );

		// Invoking parent class display function
		AbstractInstanceGUI::display();
	}

	~PlayGUI()	{
		ogre2dManager->end();
		delete ogre2dManager;
	}

	


private:
	//Manager of system of displaying 2d objects
	Ogre2dManager* ogre2dManager;

	//Text pointers
	Ogre::OverlayElement* playerData;
	Ogre::OverlayElement* mMessageConsole;

	//custom GUI objects
	Radar mRadar;
	MessageConsole* mConsole;
};




