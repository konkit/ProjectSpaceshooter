#pragma once


// Simple, primary class for gui instance for specific state
// it just displays static elements of GUI
class AbstractInstanceGUI	{
public:

	//init - run at start
	void init(std::string guiName)  	{
		//Get overlay object
			Ogre::OverlayManager* overlayManager = & Ogre::OverlayManager::getSingleton();
			overlay = overlayManager->getByName(guiName);
	}

	//display - run every frame
	void display( GameData& mGameData, TimeData _time ){
		// Show the overlay
			overlay->show();
	}

	//hide the overlay (used in state change)
	void hide()	{
		overlay->hide();
	}
	
private:
	//overlay object
	Ogre::Overlay* overlay;
};


