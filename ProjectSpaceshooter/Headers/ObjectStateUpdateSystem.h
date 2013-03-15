#pragma once

#include "Bullet.h"

//Name is to be changed - chill out :D
//I really had no idea for descriptive name for this class
class ObjectStateUpdateSystem
{
public:
	void update(GameData& mGameData, float deltaTime, Ogre::SceneManager* sceneMgr)
	{
		//for every gameobject
			//if one needs to be removed - remove it
			//if one needs to be created - create it

		if( mGameData.getPlayer()->isShooting() == true)	{

			//get player's data required to create new bullet
			GameObject* player = mGameData.getPlayer();
			float playerAngle = player->getTransformComponent().getAngle();
			Ogre::Vector3 playerPos = player->getTransformComponent().getPosition();

			//create new bullet
			mGameData.getBullets().instantiate(0, sceneMgr, playerPos, playerAngle );

			//set shooting as false
			mGameData.getPlayer()->unsetShoot();
		}

		GameCollectionIterator<Bullet> * myIterator = mGameData.getBullets().getCollection().getIterator();
		GameObject* it;
		while (myIterator->hasNext())
		{
			it = myIterator->getNext();

			it->getGamelogicComponent().decreaseTimeToLive();

			if( it->getGamelogicComponent().isStillAlive() == false )	{
				//remove from collection
				Bullet* removedObject = (Bullet*)it;
					it->getGraphicsComponent().getNode()->detachAllObjects();	//PROWIZORKA!!!
					sceneMgr->getRootSceneNode()->removeAndDestroyChild( it->getGraphicsComponent().getNode()->getName() );
				mGameData.getBullets().getCollection().deleteObject(removedObject);
			}

		}
		delete myIterator;
		

	}

};