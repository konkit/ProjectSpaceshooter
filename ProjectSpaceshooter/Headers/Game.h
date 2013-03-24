#pragma once
	
#include "InputManager.h"
#include "OgreManager.h"
#include "GameData.h"

#include "PhysicsSystem.h"
#include "ObjectStateUpdateSystem.h"
#include "CollisionSystem.h"
#include "AISystem.h"
#include "Systems.h"
#include "StateManager.h"

class Game;


/** 
  * Class enveloping Ogre3D library and simplifying usage.
  * Stores Ogre::Root and other library-specific data
  * @author 
  */





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
	
	void changeState(GameState * newState);
	const InputManager * getInputMenager() { return &mGameSystems.mInputManager;}
	OgreManager * getOgreManager() {return &mGameSystems.mOgreManager;}
	GameData * getGameData() {return &mGameSystems.mGameData;};
	void setupViewport(Ogre::Camera * camera);
private:

	SystemsSet mGameSystems;
	TimeData time;
	StateManager mStateMenager;
	// State playState;
	// etc...
};












 