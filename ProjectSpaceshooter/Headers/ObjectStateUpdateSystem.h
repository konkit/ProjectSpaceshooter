#pragma once

#include "Bullet.h"
#include "EffectObject.h"
#include "TimeUtility.h"

#include "WaveManager.h"

//Name is to be changed - chill out :D
//I really had no idea for descriptive name for this class


/** Class of Object management system
  * This is where creation and deleting of object happens
  * i.e. shooting, death, etc.
  * 
  * @author konkit 
  */
class ObjectStateUpdateSystem
{
public:

	/** Function run every frame, always at the end of main loop
	  * Checks flags (Shooting, Dead, etc) and creates or deletes objects
	  * accordingly
	  * @param mGameData - game data on which system operates
	  * @param time - time data which is needed for example in shooting
	  */
	void update(GameData& mGameData, TimeData& time);

	/** Check if any object is dead and remove it 
      * @param mGameData - game data on which system operates
	  */
	void removeDeadObjects( GameData& mGameData);

	/** Check if any object is shooting, if yes then shoot 
	  * @param mGameData - game data on which system operates
	  */
	void updateShooting( GameData &mGameData );

	/** Decrease Time To Live
      * @param mGameData - game data on which system operates
	  * @param time - TimeData object (with info about time since start and since last frame 
	  */
	void updateObjectWithTTL( GameData &mGameData, TimeData &time );

	/** Create bullet shot by given ship 
	  * @param shooter - actually shooting ship
	  * @param mGameData - game data on which system operates
	  */
	void serveShooting( Ship * shooter, GameData &mGameData );

	/** Make player dead    
	  * @param mGameData - game data on which system operates
	  */
	void destroyPlayer(GameData& mGameData);
	
	/** Create explosion when some objects are destroyed    
	  * @param removedObject - object causing an explosion
	  * @param mGameData - game data on which system operates
	  */
	void createExplosionFor( GameObject_WithCollider * removedObject, GameData& mGameData );

private:
	WaveManager mWaveManager;
};