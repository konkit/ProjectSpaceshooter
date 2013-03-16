#pragma once

#include "Bullet.h"
#include "GameCollection.h"

class BulletCollection
{
public:
	BulletCollection()
	{

	}

	void loadPrefabs()	{

	}

	//this method receives id of prefab from which it should create new object
	void instantiate(int ID, Ogre::SceneManager* sceneMgr, Ogre::Vector3 position, float angle)	
	{
		
		//Uwaga - PROWIZORKA!!!!

		//get prefab with id given
			//do zrobienia

		//create new object from prefab
		Bullet *newBullet = new Bullet;
			//set proper orientation
			newBullet->getTransformComponent().setAngle( angle );
			//set proper position
			newBullet->getTransformComponent().setPosition( position );		
			//create new sceneNode
			Ogre::SceneNode* newSceneNode = sceneMgr->getRootSceneNode()->createChildSceneNode();
			//create new entity
			Ogre::Entity* bulletEntity = sceneMgr->createEntity("bullet2.MESH");
			//attach entity to node
			newSceneNode->attachObject(bulletEntity);
			//save scene node in gameobject
			newBullet->setMesh( newSceneNode );
			//set proper velocity for bullet
			newBullet->getPhysicsComponent().setVelocity(Ogre::Vector3(0.0, 0.0, 1.0));
			//set owner
			//set power
			//set timeout before being destroyed
			//set collider

		//add it to the collection
			mCollection.addObject(newBullet);
		
	}

	GameCollection<Bullet>& getCollection()	{
		return mCollection;
	}

	GameCollectionIterator<Bullet>* getBulletIterator()
	{
		return mCollection.getIterator();
	}

private:

	GameCollection<Bullet> mCollection;
	GameCollection<BulletPrefab> mPrefabs;

};