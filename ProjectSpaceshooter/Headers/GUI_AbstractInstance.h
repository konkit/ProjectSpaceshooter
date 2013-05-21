#pragma once


// Simple, primary class for gui instance for specific state
// it just displays static elements of GUI
class AbstractInstanceGUI	{
public:

	//init - run at start
	void init(std::string guiName)  	{
		//Get overlay object
			overlayManager = & Ogre::OverlayManager::getSingleton();
			overlay = overlayManager->getByName(guiName);
	}

	//display - run every frame
	void display(){
		// Show the overlay
			overlay->show();
	}

	//hide the overlay (used in state change)
	void hide()	{
		overlay->hide();
	}
	
protected:
	//overlay object
	Ogre::OverlayManager* overlayManager;
	Ogre::Overlay* overlay;
};


