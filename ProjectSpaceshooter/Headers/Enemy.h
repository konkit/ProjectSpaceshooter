#pragma once

#include "Prefabs.h"
#include "WeaponComponent.h"
#include "HealthComponent.h"
#include "AIComponent.h"

using namespace std;

/** 
  *
  * @author Zygi
  */
class EnemyObject : public GameObject
{
public:
	EnemyObject::EnemyObject( ShipPrefab * objectTemplate, Ogre::SceneManager * _sceneMenager);
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

	AIComponent& getAIComponent()	{
		return mAIComponent;
	}
	
	bool isDead()	{
		if( mHealthComponent.isDead() == true )
			return true;

		if( GameObject::isDead() == true )
			return true;

		return false;
	}

	GameObjectType getType() {
		return GameObjectType::enemyObject;
	}
private:
//  AI component
	WeaponComponent mWeapon;
	HealthComponent mHealthComponent;
	AIComponent	mAIComponent;

};


