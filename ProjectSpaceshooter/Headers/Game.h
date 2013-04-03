#pragma once
	
#include "StateManager.h"
#include "ResoursceLoader.h"



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

    InputManager	* getInputMenager()	{ return &mGameSystems.inputManager;}
	OgreManager		* getOgreManager()	{ return &mGameSystems.ogreManager;}
	GameData		* getGameData()		{ return &mGameSystems.gameData;};

private:
	TimeData	 time;
	SystemsSet	 mGameSystems;
	ResoursceLoader resurceSystem;
	StateManager mStateMenager;
};












 