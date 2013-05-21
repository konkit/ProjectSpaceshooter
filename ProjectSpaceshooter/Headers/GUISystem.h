#pragma once

#include "ogre2d.h"

#include <OgreTextAreaOverlayElement.h>
#include <OgreFontManager.h>

#include "TimeUtility.h"
#include "GameData.h"

#include <sstream>

#include "GUI_Radar.h"
#include "MessageConsole.h"

#include "PlayGUI.h"
#include "HangarGUI.h"





class GUISystem	{
public:

	void init( Ogre::SceneManager* mSceneMgr, GAME_STATES cntState)	{
		if( cntState == GAME_STATES::PLAY )	{
			playGUI.init(mSceneMgr);
		} else if( cntState == GAME_STATES::HANGAR )	{
			hangarGUI.init(mSceneMgr);
		}
	}

	void display(  GameData& mGameData, TimeData _time, GAME_STATES cntState )	{
		if( cntState == GAME_STATES::PLAY )	{
			playGUI.display(mGameData, _time);
			hangarGUI.hide();
		} else if( cntState == GAME_STATES::HANGAR )	{
			hangarGUI.display(mGameData, _time);
			playGUI.hide();
		}
	}



private:
	PlayGUI playGUI;
	HangarGUI hangarGUI;
};




