#pragma once

#include "WeaponComponent.h"
#include "HealthComponent.h"

using namespace std;


/** 
  *
  * @author Zygi
  */
class EnemyPrefab
{
public:
	EnemyPrefab(unsigned prefabID);
	~EnemyPrefab(void);
	
	void setPrefabID(unsigned val) { mEnemyPrefabID = val; }
	void setWeaponPrefabID(unsigned val) { mWeaponPrefabID = val; }
	void setAiType(AI_TYPE val) { mMyAI = val; }
	void setMeshName(string val) { mMeshName = val; }
	void setResistance(unsigned int val) { resistance = val; }

	unsigned	 getPrefabID()   const { return mEnemyPrefabID; }
	unsigned	 getWeaponPrefabID() const { return mWeaponPrefabID; }
	AI_TYPE		 getAiType()	  const { return mMyAI; }
	std::string	 getMeshName()	  const { return mMeshName; }
	unsigned int getResistance()  const { return resistance; }
private:
	unsigned	resistance;
	unsigned	mEnemyPrefabID;
	string		mMeshName;
	AI_TYPE		mMyAI; 
	unsigned	mWeaponPrefabID;
};

/** 
  *
  * @author Zygi
  */
class EnemyObject : public GameObject
{
public:
	EnemyObject::EnemyObject( EnemyPrefab * objectTemplate, Ogre::SceneManager * _sceneMenager);
	~EnemyObject();
	unsigned int mResistance;

	void setShoot(unsigned long currentTime)	{
		mWeapon.setShoot(currentTime);
	}

	void unsetShoot()	{
		mWeapon.unsetShoot();
	}

	bool isShooting()	{
		return mWeapon.isShooting();
	}

	WeaponComponent& getCurrentWeapon()	{
		return mWeapon;
	}

	HealthComponent& getHealthComponent() {
		return mHealthComponent;
	}

	bool isDead()	{
		if( mHealthComponent.isDead() == true )
			return true;

		if( GameObject::isDead() == true )
			return true;

		return false;
	}
private:
//  AI component
	WeaponComponent mWeapon;
	HealthComponent mHealthComponent;

};


