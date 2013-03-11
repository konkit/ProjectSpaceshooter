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
					newBullet->getTransformComponent().setAngle( 
							mGameData.getPlayer()->getTransformComponent().getAngle() );
					//set proper position
					newBullet->getTransformComponent().setPosition(
							mGameData.getPlayer()->getTransformComponent().getPosition() );		
					//create new sceneNode
					Ogre::SceneNode* newSceneNode = mGameData.getSceneManager()->getRootSceneNode()
						->createChildSceneNode();


					newBullet->setMesh(mGameData.bulletEntity, newSceneNode);
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