#pragma once

#include "GUI_AbstractInstance.h"

/** GUI displayed during game over state
  * while it just displays text, it doesnt do much more than parent gui class
  *
  * @author Konkit
  */
class GameOverGUI : public AbstractInstanceGUI
{
public:
	/** init - run at start */
	void init( Ogre::SceneManager* mSceneMgr)  	{
		AbstractInstanceGUI::init("GameOverGUI");

		Ogre::OverlayContainer* playerDataPanel = static_cast<Ogre::OverlayContainer*>( overlayManager->getOverlayElement("GameOverPanel1") );
		playerScore = playerDataPanel->getChild("PlayerScoreText");
	}

	/** display - run every frame */
	void display( GameData& mGameData, TimeData _time ){

		//display player score
			std::stringstream playerScoreString;
				playerScoreString
					<<"Player score : "<<mGameData.getPlayer()->getScore();
			playerScore->setCaption( playerScoreString.str() );

		// Invoking parent class display function
		AbstractInstanceGUI::display();
	}

private:
	//Text pointers
	Ogre::OverlayElement* playerScore;
};
