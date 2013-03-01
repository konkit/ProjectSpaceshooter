#ifndef __SPACESHOOTER_GAME__
#define __SPACESHOOTER_GAME__

#include "InputManager.h"
#include "OgreManager.h"
#include "GameData.h"

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

	// State* activeState;
	// State playState;
	// etc...
};












 



#endif