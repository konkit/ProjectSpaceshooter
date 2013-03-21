#pragma once

#include "Bullet.h"
#include "GameCollection.h"


/** Collection of bullets
  * contains of collection itself as well as methods 
  * which allows adding and removal of the objects
  *
  * @author konkit
  */
class BulletCollection
{
public:
	BulletCollection()
	{

	}

	void loadPrefabs()	{

	}

	/** this method receives id of prefab from which it should create new object
	  * @param ID of prefab
	  * @param current sceneMgr
	  * @param position
	  * @param angle
	  * @param power - power of the bullet
	  * @param owner - owner GameObject (i.e. Player, Enemy) of the bullet
	  */
	void instantiate( int ID, 
					  Ogre::SceneManager* sceneMgr, 
					  Ogre::Vector3 position, 
					  Ogre::Quaternion orientation, 
					  float power,
					  GameObject* owner
					 )	
	{
		
		//Uwaga - PROWIZORKA!!!!
		//Jak b�dzie robione wczytywanie prefabow z pliku to wtedy to b�dzie si� dalo dalej rozwin��

		//create new object from prefab
		Bullet *newBullet = new Bullet("bullet2.MESH", sceneMgr);	
			//Initialize sceneNode
			newBullet->setOrientation(orientation);
			newBullet->setPosition(position);

			//set proper velocity for bullet
			newBullet->getPhysicsComponent().setVelocity(Ogre::Vector3(0.0, 0.0, 1.0));

			//set owner
			newBullet->setOwner(owner);

			//set power
			newBullet->setPower(power);

			//set timeout before being destroyed


			//set collider

		//add it to the collection
			mCollection.addObject(newBullet);	
	}

	/** function removing object from collection */
	void removeObject(Bullet* deletedObject)	{
		mCollection.deleteObject(deletedObject);
	}

	/** accessor function */
	GameCollection<Bullet>& getCollection()	{
		return mCollection;
	}

	/**accessor function */
	GameCollectionIterator<Bullet>* getBulletIterator()
	{
		return mCollection.getIterator();
	}

private:

	GameCollection<Bullet> mCollection;
	GameCollection<BulletPrefab> mPrefabs;

};