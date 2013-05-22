#pragma once
#include "PhysicsSystem.h"
#include "ObjectStateUpdateSystem.h"
#include "CollisionSystem.h"
#include "AISystem.h"

#include "DebugDrawer.h"
#include "TimeUtility.h"


/** Play state - state of normal game ( flying, shooting, etc )
 * @author
 */
class PlayState : public GameState
{
private:
public:
	PlayState(SystemsSet & _systems);

	/** all updates of systems perform here */
	virtual GAME_STATES update( SystemsSet & gameSystems, TimeData& time );

	//void loadLevelDescribe( SystemsSet & gameSystems );
	//void setCamera( Player* player );
private:
	/** create the camera */
	void createCamera();

	/** returns the next state depending on situation in game data 
	 *  for instance if player is dead then change state */
	GAME_STATES nextState( SystemsSet &gameSystems );



	int numOfFPS, currentFPSValue;
	float timeToOneSecond;
};
