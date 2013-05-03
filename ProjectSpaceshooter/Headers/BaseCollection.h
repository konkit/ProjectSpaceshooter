#pragma once

#include "Prefabs.h"
#include "Bullet.h"
#include "Enemy.h"
#include "EffectObject.h"
#include "Exceptions.h"

/** Class which is base for all collections of Enemies, Bullets etc
  * Its main parts are collection of GameObjects and collection of prefab
  *
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
			return &mPrefabs[prefabID];
		}

		using std::string;
		std::stringstream exceptionString;
		exceptionString << "There are no prefab with id =" << prefabID << " in prefab collection " << collName;
		throw exception(exceptionString.str().c_str());
	}
	void setCountOfPrefab(unsigned max_id)
	{
		mPrefabs.resize(max_id);
	}

protected:

	GameCollection<TObject> mCollection;
	vector<TPrefab> mPrefabs;
	std::string collName;
};

class EnemyAndShipPrefabsCollections : public BaseCollection<ShipPrefab, EnemyObject>
{
public: 
	EnemyAndShipPrefabsCollections() : BaseCollection("Enemy And ShipPrefabs Collections"), mWeaponCollection(20) {}
 	EnemyObject * instantiateEnemy(int ID, AI_TYPE myAi, Ogre::SceneManager* sceneMgr)
	{
			//get prefab with id given
			const ShipPrefab* currentPrefab = getPrefab(ID);
			const WeaponPrefab* weaponPref = &mWeaponCollection[currentPrefab->getWeaponPrefabID()];
			//create new object from prefab
			EnemyObject * newObject = new EnemyObject(currentPrefab, weaponPref, myAi, sceneMgr);

			//add it to the collection
			mCollection.addObject(newObject);
			return newObject;
	}
	vector<WeaponPrefab> getWeaponCollection() const { return mWeaponCollection; }
	const WeaponPrefab * getWeaponPrefab(unsigned prefabID) const 
	{ 
		if (prefabID < mWeaponCollection.size())
		{
			return &mWeaponCollection[prefabID];
		}
		using std::string;
		std::stringstream exceptionString;
		exceptionString << "There are no prefab with id =" << prefabID << " in weapon prefab collection ";
		throw My_Exception(exceptionString.str().c_str());
	}
	void addWeaponPrefab(const WeaponPrefab& _weaponPrefab)
	{
		if (&_weaponPrefab == NULL)
		{
			throw My_Exception("addWeaponPrefab: Can't add NULL Weapon Prefab");
		}
		unsigned prefabID = _weaponPrefab.getPrefabID(); 
		if (prefabID >= mWeaponCollection.size())
		{
			mWeaponCollection.resize(prefabID+1);
		}
		mWeaponCollection[prefabID] = _weaponPrefab;
	}

	void setCountOfWeaponPrefab(unsigned max_id){ mWeaponCollection.resize(max_id);}
	void setCountOfShipPrefab(unsigned max_id){ mPrefabs.resize(max_id);}
private:
	vector<WeaponPrefab> mWeaponCollection;
};

class BulletCollection : public BaseCollection<BulletPrefab, Bullet>
{

	//Wywo�anie tego musi by� po wczytaniu prefab�w - �eby wiedzie� jak wielki ma by� wektor
	void initializeBullet(Ogre::SceneManager * sceneManager)
	{
		for(int i = 1; i <= mPrefabs.size(); i++)
		{
			for (int j = 0; j < preCreatedCount; j++)
			{
				BulletPrefab * prefab = getPrefab(i);
				Bullet * tmp =  new Bullet(prefab, sceneManager);
				createdBullet[i].addObject(tmp); 
			}
		}
	}
	Bullet * instantiate(unsigned prefabID)
	{
		Bullet * tmp = createdBullet[prefabID].detachFirst();
		mCollection.addObject(tmp);
		return tmp;
	}
	void destroyBullet(GameCollectionIterator<Bullet> &it)
	{
		Bullet *tmp = mCollection.detach(it); // U�ywam it �eby nie traci� czasu na ponowne wyszukiwanie obiektu na li��ie, a tak u�yj� danych zapisanych w iteratorze
//		createdBullet[tmp->getPrefabID].addObject(tmp);
	}
private:
	const int preCreatedCount;
	std::vector<GameCollection<Bullet>> createdBullet;
};