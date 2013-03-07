#pragma once

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


			//set shooting as false
			mGameData.getPlayer()->unsetShoot();
		}

	}

};