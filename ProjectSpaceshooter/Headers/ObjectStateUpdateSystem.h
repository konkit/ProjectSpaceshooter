#pragma once

#include "Bullet.h"
#include "EffectObject.h"
#include "Systems.h"

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
	void removeDeadObjects( GameData& mGameData);
	void createExplosionFor( GameObject_WithCollider * removedObject, GameData& mGameData );
};