#pragma once

#include "Enemy.h"
#include "GameCollection.h"
#include "EnemyCollection.h"
#include <sstream>
class EnemyCollection
{
public:
	EnemyCollection()
	{

	}

	void loadPrefabs()	{

	}

	//this method receives id of prefab from which it should create new object
	EnemyObject * instantiate(int ID, Ogre::SceneManager* sceneMgr)	{
		//zygi, zrób tak, by by³o dobrze :D

		//get prefab with id given
		EnemyPrefab* currentPrefab; // = ...

		//create new object from prefab
		EnemyObject* newEnemy = new EnemyObject(currentPrefab, sceneMgr);

		//add it to the collection
		mCollection.addObject(newEnemy);
		return newEnemy;
	}
	void operator-=(EnemyObject * enemyToRemove)
	{
		mCollection -= enemyToRemove;
	}
	GameCollection<EnemyObject>& getCollection()	{
		return mCollection;
	}




private:
	EnemyPrefab * findPrefab(unsigned prefabID)
	{
		GameCollectionIterator<EnemyPrefab> * it = mPrefabs.getIterator();
		EnemyPrefab * tmpPrefab;
		while(it->hasNext())
		{
			tmpPrefab = it->getNext();
			if (tmpPrefab->getEnemyPrefabID() == prefabID)
			{
				return tmpPrefab;
			}
		}
		using std::string;
		std::stringstream exceptionString;
		exceptionString << "There are no prefab with id =" << prefabID << " in prefab collection";
		throw exception(exceptionString.str().c_str());
	};
	GameCollection<EnemyObject> mCollection;
	GameCollection<EnemyPrefab> mPrefabs;

};