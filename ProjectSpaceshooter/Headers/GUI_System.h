#pragma once

#include "ogre2d.h"

#include <OgreTextAreaOverlayElement.h>
#include <OgreFontManager.h>

#include "TimeUtility.h"
#include "GameData.h"

#include <sstream>

#include "GUI_Radar.h"
#include "GUI_MessageConsole.h"

#include "GUI_Play.h"
#include "GUI_Hangar.h"
#include "GUI_GameOver.h"




/** Systems which governs displaying of GUI
  */
class GUISystem	{
public:
	//init GUI- run at creation of state
	void init( Ogre::SceneManager* mSceneMgr, GAME_STATES cntState)	{
		//Load Font
			Ogre::FontManager &fontMgr = Ogre::FontManager::getSingleton();
			Ogre::ResourcePtr font = fontMgr.getByName("MyFont");
			font->load();

		if( cntState == GAME_STATES::PLAY )	{
			playGUI.init(mSceneMgr);
		} else if( cntState == GAME_STATES::HANGAR )	{
			hangarGUI.init(mSceneMgr);
		} else if( cntState == GAME_STATES::GAME_OVER )	{
			gameOverGUI.init(mSceneMgr);
		}
	}

	//display the GUI - run every frame
	void display(  GameData& mGameData, TimeData _time, GAME_STATES cntState )	{
		if( cntState == GAME_STATES::PLAY )	{
			playGUI.display(mGameData, _time);
			hangarGUI.hide();
			gameOverGUI.hide();
		} else if( cntState == GAME_STATES::HANGAR )	{
			hangarGUI.display();
			playGUI.hide();
			gameOverGUI.hide();
		} else if( cntState == GAME_STATES::GAME_OVER )	{
			gameOverGUI.display();
			playGUI.hide();
			hangarGUI.hide();
		}
	}

private:
	PlayGUI playGUI;
	HangarGUI hangarGUI;
	GameOverGUI gameOverGUI;
};



