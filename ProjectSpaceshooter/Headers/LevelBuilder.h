#pragma once
#include "TimeUtility.h"


/** Level builder state - loads level from file
 * @author 
 */
class LevelBuilder : public GameState
{
public:
	LevelBuilder(SystemsSet & gameSystems);
	~LevelBuilder();

	/** update method - after finished load it changes   */
	virtual GAME_STATES update( SystemsSet & gameSystems, TimeData& time );

private:
	/** init enemy spawners etc. */
	void loadLevelDescription( SystemsSet & gameSystems );
		
	/** set gameobjects on scene */
	void buildPlayScene( SystemsSet & gameSystems, TimeData& time );

	/** Create camera - Lever builder required camera because in refuter it will show progress bar */
	virtual void createCamera();

	/** method changes state to the PlayState */
	virtual GAME_STATES nextState( SystemsSet & gameSystems );

	/** attach camera to player */
	void attachCameraToPlayer(SystemsSet & gameSystems);
};