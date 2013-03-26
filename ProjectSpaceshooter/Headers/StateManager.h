#pragma once
#include "Systems.h"
#include "GameState.h"
class Game;

class GameState
{
protected:
	GameData * mGameData;

	Ogre::SceneManager* mSceneMgr;
	Ogre::Camera * mCamera;
public:
	Ogre::SceneManager* getSceneMgr(){return mSceneMgr;}
	GameState(){}
	virtual GAME_STATES update(SystemsSet & gameSystems, TimeData& time) = 0;
	virtual ~GameState(void){delete mSceneMgr;}
	Ogre::Camera * getCamera() {return mCamera;}
};

class StateManager
{
public:
	StateManager(SystemsSet * _systems);
	virtual bool update( SystemsSet & gameSystems, TimeData& time );
	void renderOneFrame();
	void changeState(GAME_STATES * nextState);
	~StateManager(void);
private:
	OgreManager * mOgreManager;
	GAME_STATES activeStateName;
	GameState * activeState;
	GameState * pause;
	GameState * play;
	GameState * hangar;
	GameState * state;
	GameState * builder;
};

