#pragma once

#include "InputManager.h"
#include "OgreManager.h"
#include "GameData.h"

#include "PhysicsSystem.h"
#include "GraphicsSystem.h"

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

		//init systems
		mGraphicsSystem.init( &mOgreManager );

		while(true)
		{
			//update input from player
			/* powinno byc updateInput( mGameData ) */
			if(mInputManager.updateInput(mGameData)==false)
				return false;

			//std::cout<<"Player velocity = "<<mGameData.getPlayer()->getPhysicsComponent().velocityX<<", "<<
			//								mGameData.getPlayer()->getPhysicsComponent().velocityY<<", "<<
			//								mGameData.getPlayer()->getPhysicsComponent().velocityZ<<"\n";

			// game logic
			/* tu powinny byæ wszystkie update'y systemów
			   aiSystem.update( mGameData );
			   physicsSystem.update( mGameData );
			   collisionSystem.update( mGameData );*/

			mPhysicsSystem.update( mGameData );



			// Render a frame
			mGraphicsSystem.updateNodesAndDraw(mGameData);

			//std::cout<<"Player pos = "<<mGameData.getPlayer()->getTransformComponent().getX()<<", "<<
			//							mGameData.getPlayer()->getTransformComponent().getY()<<", "<<
			//							mGameData.getPlayer()->getTransformComponent().getZ()<<"\n";

		}

		return true;
	}

private:
	InputManager mInputManager;
	OgreManager mOgreManager;
	GameData mGameData;	

	PhysicsSystem mPhysicsSystem;
	GraphicsSystem mGraphicsSystem;

	// State* activeState;
	// State playState;
	// etc...
};











 