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


			//instantiate bullet
				Bullet* newBullet = new Bullet;
					//set proper orientation
					newBullet->getTransformComponent().setAngle( 
							mGameData.getPlayer()->getTransformComponent().getAngle() );
					//set proper position
					newBullet->getTransformComponent().setPosition(
							mGameData.getPlayer()->getTransformComponent().getPosition() );		
					//create new sceneNode
					Ogre::SceneNode* newSceneNode = sceneMgr->getRootSceneNode()->createChildSceneNode();

					Ogre::Entity* bulletEntity = sceneMgr->createEntity("bullet2.MESH");

					newSceneNode->attachObject(bulletEntity);

					newBullet->setMesh( newSceneNode );

					newBullet->getPhysicsComponent().setVelocity(Ogre::Vector3(0.0, 0.0, 1.0));

					//set owner
					//set power
					//set timeout before being destroyed
					//set collider
					// ... or copy from prefab

				//add ready object to Collection
				mGameData.getBullets().addObject(newBullet);

			//set shooting as false
			mGameData.getPlayer()->unsetShoot();
		}

	}

};