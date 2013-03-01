#pragma once

#include "InputManager.h"
#include "OgreManager.h"
#include "GameData.h"

// Main class in this game, contains main loop.
// Governs Systems, managers, STATES!
class Game 
{
public:
	bool Game::run()
	{ 
		//Initialize ogre
		mOgreManager.initOgre();
		//Initialize OIS
		mInputManager.initOIS( mOgreManager.getWindowHandle() );

		//Initialize scene - setup all cameras, entities, etc
		mGameData.initScene( mOgreManager.getRoot(), mOgreManager.getWindowHandle() );
		mGameData.setScene();

		while(true)
		{
			//update input from player
			/* powinno byc updateInput( mGameData ) */
			if(mInputManager.updateInput(mGameData.camX, mGameData.camY, mGameData.camZ)==false)
				return false;



			//temporary game logic
			/* to powinno byc gdzies w jakims systemie */
			//mGameData.mCamera->setPosition(Ogre::Vector3(mGameData.camX, mGameData.camY, mGameData.camZ));
			//mGameData.mCamera->lookAt(mGameData.camX, 0.0, mGameData.camZ);
			//mGameData.mCamera->lookAt(0.0, 0.0, 0.0);
			mGameData.updateScene();

			// Render a frame
			if(! mOgreManager.getRoot()->renderOneFrame()) return false;
		}

		return true;
	}

private:
	InputManager mInputManager;
	OgreManager mOgreManager;
	GameData mGameData;	

	// State* activeState;
	// State playState;
	// etc...
};











 