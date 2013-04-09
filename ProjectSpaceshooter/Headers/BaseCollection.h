#pragma once

#include "Prefabs.h"
#include "Bullet.h"
#include "Enemy.h"
#include "EffectObject.h"

/** Class which is base for all collections of Enemies, Bullets etc
  * Its main parts are collection of GameObjects and collection of prefab
  *
  */
template<class TPrefab, class TObject>
class BaseCollection
{
public:
	void loadPrefabs();

	TObject* instantiate(int ID, Ogre::SceneManager* sceneMgr)	{
		//get prefab with id given
		TPrefab* currentPrefab = getPrefab(ID);

		//create new object from prefab
		TObject* newObject = new TObject(currentPrefab, sceneMgr);

		//add it to the collection
		mCollection.addObject(newObject);
		return newObject;
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
	void addPrefab(TPrefab* newPrefab) {
		mPrefabs += newPrefab;
	}

private:


	TPrefab* getPrefab(int prefabID)	{
		GameCollectionIterator<TPrefab>  it = mPrefabs.getIterator();
		TPrefab * tmpPrefab;
		while(it.hasNext())
		{
			tmpPrefab = it.getNext();
			if (tmpPrefab->getPrefabID() == prefabID)
			{
				return tmpPrefab;
			}
		}

		using std::string;
		std::stringstream exceptionString;
		exceptionString << "There are no prefab with id =" << prefabID << " in prefab collection";
		throw exception(exceptionString.str().c_str());
	}

	GameCollection<TObject> mCollection;
	GameCollection<TPrefab> mPrefabs;

};
