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
	/**
	 * 
	 * @param name 
	 * @author konkit
	 */
	BaseCollection(std::string name) : collName(name) {}


	/**
	 * Create new object with data from prefab with given ID
	 * @return created object
	 * @param ID 
	 * @param sceneMgr 
	 * @author konkit
	 */
	TObject* instantiate(int ID, Ogre::SceneManager* sceneMgr)	{

		//create new object from prefab
		TObject* newObject = new TObject(getPrefab(ID), sceneMgr);

		//add it to the collection
		mCollection.addObject(newObject);
		return newObject;
	}

	/**
	 * Add object to collection 
	 * @param object 
	 * @author konkit
	 */
	void addObjectToCollection(TObject * object)
	{
		mCollection.addObject(object);
	}

	/**
	 * remove object from collection
	 * @param enemyToRemove 
	 * @author konkit
	 */
	void operator-=(TObject * enemyToRemove)
	{
		mCollection -= enemyToRemove;
	}

	/**
	 * @return collection
	 * @author konkit
	 */
	GameCollection<TObject>& getCollection()	{
		return mCollection;
	}

	/**
	 * @return iterator for collection 
	 * @author konkit
	 */
	GameCollectionIterator<TObject> getIterator()
	{
		return mCollection.getIterator();
	}

	/**
	 * adds new prefab to prefab collection 
	 * @param newPrefab 
	 * @author konkit
	 */
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

	/**
	 * @return prefab with given ID 
	 * @param prefabID 
	 * @author konkit
	 */
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

	/**
	 * Set capacity of prefab collection to given
	 * @param max_id 
	 * @author Zyga
	 */
	void setCountOfPrefab(unsigned max_id)
	{
		mPrefabs.resize(max_id);
	}

	/**
	 * @return returns size of prefab collection
	 * @author Zyga
	 */
	unsigned getNumberOfPrefabs(){ return mPrefabs.size() -1;}

	/**
	 * @return true if there isn't any objects in collection
	 * @author konkit
	 */
	bool isCollectionEmpty()	{
		return mCollection.isEmpty();
	}

protected:
	GameCollection<TObject> mCollection;
	vector<TPrefab> mPrefabs;
	std::string collName;
};

