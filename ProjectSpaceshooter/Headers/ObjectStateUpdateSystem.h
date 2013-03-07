#pragma once

#include "Bullet.h"

//Name is to be changed - chill out :D
//I really had no idea for descriptive name for this class
class ObjectStateUpdateSystem
{
public:
	void update(GameData& mGameData, float deltaTime)
	{
		//for every gameobject
			//if one needs to be removed - remove it
			//if one needs to be created - create it

		if( mGameData.getPlayer()->isShooting() == true)	{
			//instantiate bullet
				Bullet* newBullet = new Bullet;
					//set proper orientation
						//orientation as shooter (player/enemy)
						//but a little in front of it
					//set mesh!!! ?
					//set owner
					//set power
					//set timeout before being destroyed
					//set collider
					// ... or copy from prefab

				//add ready object to Collection


			//set shooting as false
			mGameData.getPlayer()->unsetShoot();
		}

	}

};