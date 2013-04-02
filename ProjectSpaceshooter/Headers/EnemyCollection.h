#pragma once

#include "Enemy.h"
#include "GameCollection.h"
#include <sstream>
#include <vector>

/** 
  * Collection of enemies
  * @author Zygi
  */

class EnemyCollection
{
public:
	EnemyCollection()
	{

	}

	void loadPrefabs()	{
		//TODO Iniciajlizowaæ nowe obiekty z plików
		EnemyPrefab myEnemy(1);
		myEnemy.setAiType(AI_TYPE::fighter);
		myEnemy.setMeshName("smallfighter.MESH");
		myEnemy.setResistance(1000);
		myEnemy.setWeaponPrefabID(1);
		addPrefab(myEnemy);
	}

	//this method receives id of prefab from which it should create new object
	EnemyObject * instantiate(int ID, Ogre::SceneManager* sceneMgr)	
	{
		//zygi, zrób tak, by by³o dobrze :D

		//get prefab with id given
		EnemyPrefab* currentPrefab = findPrefab(ID);

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

	GameCollectionIterator<EnemyObject> * getEnemyIterator()
	{
		return mCollection.getIterator();
	}
	void addPrefab(EnemyPrefab _enemyPrefab);
	void setNumberOfPrefabs(int count){mPrefabs.resize(count);}

private:
	EnemyPrefab * findPrefab(unsigned prefabID)
	{
		return &mPrefabs[prefabID];		
		using std::string;
		std::stringstream exceptionString;
		exceptionString << "There are no prefab with id =" << prefabID << " in prefab collection";
		throw exception(exceptionString.str().c_str());
	};
	GameCollection<EnemyObject> mCollection;
	//GameCollection<EnemyPrefab> mPrefabs;
	std::vector<EnemyPrefab> mPrefabs;
};
