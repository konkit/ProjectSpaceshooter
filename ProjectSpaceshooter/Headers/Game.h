#pragma once

#include "InputManager.h"
#include "OgreManager.h"
#include "GameData.h"

#include "PhysicsSystem.h"
#include "GraphicsSystem.h"
#include "ObjectStateUpdateSystem.h"

class Game;

class GameState
{
protected:
	Ogre::SceneManager* mSceneMgr;
	Game * mGame;
	Ogre::Camera * mCamera;
public:
	Ogre::SceneManager* getSceneMgr(){return mSceneMgr;}
	GameState(Game * game): mGame(game){}
	virtual bool update() = 0;
	virtual ~GameState(void){}
	Ogre::Camera * getCamera() {return mCamera;}
};




// Main class in this game, contains main loop.
// Governs Systems, managers, STATES!
class Game 
{
public:
	Game();
	~Game();
	void initializeGame();
	void run();
	
	GameState * getPause() const { return pause; }
	GameState * getPlay() const { return play; }
	GameState * getHangar() const { return hangar; }
	GameState * getLevelBuilder() const { return builder; }
	void changeState(GameState * newState);
	const InputManager * getInputMenager() { return &mInputManager;}
	OgreManager * getOgreManager() {return &mOgreManager;}
	GameData * getGameData() {return &mGameData;};
	void setupViewport(Ogre::Camera * camera);
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
	ObjectStateUpdateSystem mObjectStateSystem;

	// State* activeState;
	// State playState;
	// etc...
};












 