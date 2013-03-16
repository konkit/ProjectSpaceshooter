#pragma once

#include "InputManager.h"
#include "OgreManager.h"
#include "GameData.h"

#include "PhysicsSystem.h"
#include "GraphicsSystem.h"
#include "ObjectStateUpdateSystem.h"
#include "Systems.h"

class Game;


/** 
  * Class enveloping Ogre3D library and simplifying usage.
  * Stores Ogre::Root and other library-specific data
  * @author 
  */
class GameState
{
protected:
	Ogre::SceneManager* mSceneMgr;
	Game * mGame;
	Ogre::Camera * mCamera;
public:
	Ogre::SceneManager* getSceneMgr(){return mSceneMgr;}
	GameState(Game * game): mGame(game){}
	virtual bool update(SystemsSet & gameSystems, TimeData& time) = 0;
	virtual ~GameState(void){}
	Ogre::Camera * getCamera() {return mCamera;}
};




/** 
  * Class enveloping Ogre3D library and simplifying usage.
  * Governs Systems, managers, STATES!
  * @author
  */
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
	const InputManager * getInputMenager() { return &mGameSystems.mInputManager;}
	OgreManager * getOgreManager() {return &mGameSystems.mOgreManager;}
	GameData * getGameData() {return &mGameSystems.mGameData;};
	void setupViewport(Ogre::Camera * camera);
private:
	GameState * pause;
	GameState * play;
	GameState * hangar;
	GameState * state;
	GameState * builder;
	SystemsSet mGameSystems;
	TimeData time;
	// State playState;
	// etc...
};












 