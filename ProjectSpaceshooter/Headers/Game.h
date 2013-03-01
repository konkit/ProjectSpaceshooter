#ifndef __SPACESHOOTER_GAME__
#define __SPACESHOOTER_GAME__

#include "InputManager.h"
#include "OgreManager.h"
#include "GameData.h"
#include "GameState.h"
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
	GameState * betLeveBuilder() const { return builder; }
	GameState * changeState(GameState * newState) {state = newState; }
	InputManager * getInputMenager() const { return &mInputManager;}
	OgreManager * getOgreManager() const {return &mOgreManager;}
	GameData * getGameData() const {return &mGameData};
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