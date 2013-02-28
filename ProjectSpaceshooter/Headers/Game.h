#ifndef __SPACESHOOTER_GAME__
#define __SPACESHOOTER_GAME__

#include "InputManager.h"
#include "OgreManager.h"
#include "GameData.h"


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
			mGameData.mCamera->setPosition(Ogre::Vector3(mGameData.camX, mGameData.camY, mGameData.camZ));

			// Render a frame
			if(! mOgreManager.getRoot()->renderOneFrame()) return false;
		}

		return true;
	}

private:
	InputManager mInputManager;
	OgreManager mOgreManager;
	GameData mGameData;	
};











 



#endif