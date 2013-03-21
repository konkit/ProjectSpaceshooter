#pragma once
#include "Systems.h"
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
	virtual bool update(SystemsSet & gameSystems, TimeData& time) = 0;
	virtual ~GameState(void){}
	Ogre::Camera * getCamera() {return mCamera;}
};

class StateManager
{
public:
	StateManager(void);
	virtual bool update( SystemsSet & gameSystems, TimeData& time );
	~StateManager(void);
private:
	GameState * pause;
	GameState * play;
	GameState * hangar;
	GameState * state;
	GameState * builder;
};

