#pragma once

#include "Bullet.h"
#include "Systems.h"
//Name is to be changed - chill out :D
//I really had no idea for descriptive name for this class
class ObjectStateUpdateSystem
{
public:
	void update(GameData& mGameData, TimeData& time)
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
			mGameData.getBullets().instantiate(0, mGameData.getSceneManagerFor(GAME_STATES::PLAY), playerPos, playerAngle);

			//set shooting as false
			mGameData.getPlayer()->unsetShoot();
		}
		mGameData.getLevelDescription().spawn(mGameData, time.currentTime);
	}

};