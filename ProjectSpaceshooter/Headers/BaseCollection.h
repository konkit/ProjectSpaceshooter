#pragma once

#include "Prefabs.h"
#include "Bullet.h"
#include "Enemy.h"
#include "EffectObject.h"
#include "Exceptions.h"

/** Class which is base for all collections of Enemies, Bullets etc
  * Its main parts are collection of GameObjects and collection of prefab
  *
  * @author konkit
  */
template<class TPrefab, class TObject>
class BaseCollection
{
public:
	BaseCollection(std::string name) : collName(name) {}
	TObject* instantiate(int ID, Ogre::SceneManager* sceneMgr)	{

		//create new object from prefab
		TObject* newObject = new TObject(getPrefab(ID), sceneMgr);

		//add it to the collection
		mCollection.addObject(newObject);
		return newObject;
	}

	void addObjectToCollection(TObject * object)
	{
		mCollection.addObject(object);
	}
	void operator-=(TObject * enemyToRemove)
	{
		mCollection -= enemyToRemove;
	}

	GameCollection<TObject>& getCollection()	{
		return mCollection;
	}

	GameCollectionIterator<TObject> getIterator()
	{
		return mCollection.getIterator();
	}
	void addPrefab(const TPrefab* newPrefab) {
		if (&newPrefab == NULL)
		{
			throw My_Exception("addPrefab: Can't add NULL Weapon Prefab");
		}
		unsigned prefabID = newPrefab->getPrefabID(); 
		if (prefabID >= mPrefabs.size())
		{
			mPrefabs.resize(prefabID+1);
		}
		mPrefabs[prefabID] = *newPrefab;
	}
	TPrefab* getPrefab(int prefabID)	
	{
		if(prefabID < mPrefabs.size())
		{
			if(mPrefabs[prefabID].getPrefabID() != 0)
				return &mPrefabs[prefabID];
			else
			{
				throw PrefabException("There is no prefab with id = " + to_string(prefabID), PrefabExceptionType::NO_PREFAB);
			}
		}

		throw PrefabException("There is no prefab with id = " + to_string(prefabID), PrefabExceptionType::NO_PREFAB);
	}
	void setCountOfPrefab(unsigned max_id)
	{
		mPrefabs.resize(max_id);
	}
	unsigned getNumberOfPrefabs(){ return mPrefabs.size() -1;}
protected:

	GameCollection<TObject> mCollection;
	vector<TPrefab> mPrefabs;
	std::string collName;
};

