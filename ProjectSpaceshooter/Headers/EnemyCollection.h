#pragma once

#include "Enemy.h"
#include "GameObjectsCollection.h"

class EnemyCollection
{
public:
	EnemyCollection()
	{

	}

	void loadPrefabs()	{

	}

	//this method receives id of prefab from which it should create new object
	void instantiate(int ID, Ogre::SceneManager* sceneMgr)	{
		//zygi, zrób tak, by by³o dobrze :D

		//get prefab with id given
		EnemyPrefab* currentPrefab; // = ...

		//create new object from prefab
		EnemyObject* newEnemy = new EnemyObject(currentPrefab, sceneMgr);

		//add it to the collection
		mCollection.addObject(newEnemy);
	}

	GameObjectsCollection<EnemyObject>& getCollection()	{
		return mCollection;
	}




private:

	GameObjectsCollection<EnemyObject> mCollection;
	GameObjectsCollection<EnemyPrefab> mPrefabs;

};