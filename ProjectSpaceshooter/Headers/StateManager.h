#pragma once
#include "Systems.h"
#include "GameState.h"
#include "PlayState.h"
#include "PauseState.h"
#include "HangarState.h"
#include "LevelBuilder.h"
#include "GameOver.h"


/** State manager - governs changes of game states 
*/
class StateManager
{
public:
	StateManager();
	~StateManager(void);
	virtual bool update( SystemsSet & gameSystems, TimeData& time );
	void changeState(GAME_STATES nextState, SystemsSet & gameSystems);
	void setupViewport(OgreManager & _ogreManager, Ogre::Camera * camera );
	GameState * getStateFor( GAME_STATES nextState );
	void initStateManager( SystemsSet & _systems );
private:
	OgreManager * mOgreManager;
	GAME_STATES activeStateName;
	GameState * activeState;
	GameState * pause;
	GameState * play;
	GameState * hangar;
	GameState * builder;
	GameState * gameOver;
};

