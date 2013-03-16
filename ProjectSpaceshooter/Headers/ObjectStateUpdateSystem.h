#pragma once

#include "Bullet.h"
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
	void update(GameData& mGameData, TimeData& time)
	{
		//for every gameobject
			//if one needs to be removed - remove it
			//if one needs to be created - create it

		//creating bullets when player is shooting
		if( mGameData.getPlayer()->isShooting() == true)	{
			//get player's data required to create new bullet
			GameObject* player = mGameData.getPlayer();
			float playerAngle = player->getTransformComponent().getAngle();
			Ogre::Vector3 playerPos = player->getTransformComponent().getPosition();

			//create new bullet
			mGameData.getBullets().instantiate(0, mGameData.getSceneManagerFor(GAME_STATES::PLAY), playerPos, playerAngle);

			//set shooting as false
			mGameData.getPlayer()->unsetShoot();
		}

		//spawning enemies
		mGameData.getLevelDescription().spawn(mGameData, time.currentTime);

		//deleting bullets when time to Live is up.
		GameCollectionIterator<Bullet> * myIterator = mGameData.getBullets().getBulletIterator();
		GameObject* it;
		while (myIterator->hasNext())
		{
			it = myIterator->getNext();

			it->getGamelogicComponent().decreaseTimeToLive();

			if( it->getGamelogicComponent().isStillAlive() == false )	{
				//remove from collection
				Bullet* removedObject = (Bullet*)it;
					it->getGraphicsComponent().getNode()->detachAllObjects();	//PROWIZORKA!!!
					mGameData.getSceneManagerFor(GAME_STATES::PLAY)->getRootSceneNode()->removeAndDestroyChild( it->getGraphicsComponent().getNode()->getName() );
				mGameData.getBullets().getCollection().deleteObject(removedObject);
			}

		}
		delete myIterator;
		

	}

};