#pragma once

#include "Prefabs.h"
#include "WeaponComponent.h"
#include "HealthComponent.h"

using namespace std;

/** 
  *
  * @author Zyga
  */
class EnemyObject : public GameObject
{
public:
	EnemyObject::EnemyObject( ShipPrefab * objectTemplate, Ogre::SceneManager * _sceneMenager);
	~EnemyObject();

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
	void setWeapon(const WeaponPrefab * prefab){mWeapon.setWeapon(prefab);}
	unsigned getWeaponPrefabID() const { return mWeapon.getWeaponPrefabID(); }
	AI_TYPE getAI() const { return myAI; }
	void setAI(AI_TYPE val) { myAI = val; }
private:
//  AI component
	AI_TYPE myAI;
	WeaponComponent mWeapon;
	HealthComponent mHealthComponent;

};


