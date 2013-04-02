#pragma once

#include "Prefabs.h"
#include "WeaponComponent.h"
#include "HealthComponent.h"

using namespace std;

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


