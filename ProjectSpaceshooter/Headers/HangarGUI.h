#pragma once

class HangarGUI
{
public:

	//init - run at start
	void init( Ogre::SceneManager* mSceneMgr)  	{
		//2D graphics
			ogre2dManager = new Ogre2dManager;
			ogre2dManager->init(mSceneMgr, Ogre::RENDER_QUEUE_OVERLAY, true);

		//Text Stuff
			//Load Font
			Ogre::FontManager &fontMgr = Ogre::FontManager::getSingleton();
			Ogre::ResourcePtr font = fontMgr.getByName("MyFont");
			font->load();

			//Get overlay object
			Ogre::OverlayManager* overlayManager = & Ogre::OverlayManager::getSingleton();
			overlay = overlayManager->getByName("HangarGUI");
	}

	//display - run every frame
	void display( GameData& mGameData, TimeData _time ){
		// Show the overlay
			overlay->show();
	}


	~HangarGUI()	{
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
};