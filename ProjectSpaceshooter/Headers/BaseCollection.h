#pragma once

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

	GameCollectionIterator<TObject> * getIterator()
	{
		return mCollection.getIterator();
	}

private:

	void addPrefab(TPrefab* newPrefab) {
		mPrefabs += newPrefab;
	}

	TPrefab* getPrefab(int prefabID)	{
		GameCollectionIterator<TPrefab> * it = mPrefabs.getIterator();
		TPrefab * tmpPrefab;
		while(it->hasNext())
		{
			tmpPrefab = it->getNext();
			if (tmpPrefab->getPrefabID() == prefabID)
			{
				return tmpPrefab;
			}
		}
		delete it;

		using std::string;
		std::stringstream exceptionString;
		exceptionString << "There are no prefab with id =" << prefabID << " in prefab collection";
		throw exception(exceptionString.str().c_str());
	}

	GameCollection<TObject> mCollection;
	GameCollection<TPrefab> mPrefabs;

};


//TYMCZASOWY WORKAROUND - dopoki nie bêdzie ResourceLoadera od Zygiego
//Inline, bo siê kompilator czepia
template<>
inline void BaseCollection<EnemyPrefab, EnemyObject>::loadPrefabs()	{
	//TODO Iniciajlizowaæ nowe obiekty z plików
	EnemyPrefab * myEnemy = new EnemyPrefab(1); 
	addPrefab(myEnemy);
	myEnemy->setAiType(AI_TYPE::fighter);
	myEnemy->setMeshName("smallfighter.MESH");
	myEnemy->setResistance(1000);
}

template<>
inline void BaseCollection<BulletPrefab, Bullet>::loadPrefabs()	{
	BulletPrefab * myBullet = new BulletPrefab(1); 
	addPrefab(myBullet);
	myBullet->setBulletPower(5.0);
	myBullet->setMeshName("bullet2.MESH");

	myBullet->setMaxVelocity(500);
	myBullet->setVelocityVector(Ogre::Vector3(0.0, 0.0, 1.0));
}

template<>
inline void BaseCollection<EffectPrefab, EffectObject>::loadPrefabs() {
	EffectPrefab* myEffect = new EffectPrefab(1);
	addPrefab(myEffect);
	myEffect->setParticleSystemName( "explosionTemplate" );
}

