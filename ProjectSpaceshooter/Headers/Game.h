#pragma once

#include "InputManager.h"
#include "OgreManager.h"
#include "GameData.h"

#include "PhysicsSystem.h"
#include "GraphicsSystem.h"

class Game;
class GameState
{
protected:
	Ogre::SceneManager* mSceneMgr;
	Game * game;
public:
	Ogre::SceneManager* getSceneMgr(){return mSceneMgr;};
	GameState(Game * game): game(game){};
	virtual bool update() = 0;
	virtual ~GameState(void){};
};
// Main class in this game, contains main loop.
// Governs Systems, managers, STATES!
class Game 
{
public:
	Game();
	~Game();
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


			mGraphicsSystem.updateNodesAndDraw(mGameData);

			//std::cout<<"Player pos = "<<mGameData.getPlayer()->getTransformComponent().getX()<<", "<<
			//							mGameData.getPlayer()->getTransformComponent().getY()<<", "<<
			//							mGameData.getPlayer()->getTransformComponent().getZ()<<"\n";


	void initializeGame();
	bool run();
	GameState * getPause() const { return pause; }
	GameState * getPlay() const { return play; }
	GameState * getHangar() const { return hangar; }
	GameState * getLevelBuilder() const { return builder; }
	GameState * changeState(GameState * newState) {state = newState; }
	const InputManager * getInputMenager() { return &mInputManager;}
	OgreManager * getOgreManager() {return &mOgreManager;}
	GameData * getGameData() {return &mGameData;};
private:
	GameState * pause;
	GameState * play;
	GameState * hangar;
	GameState * state;
	GameState * builder;
	InputManager mInputManager;
	OgreManager mOgreManager;
	GameData mGameData;	

	PhysicsSystem mPhysicsSystem;
	GraphicsSystem mGraphicsSystem;

	// State* activeState;
	// State playState;
	// etc...
};












 