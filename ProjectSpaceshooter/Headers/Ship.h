#pragma once
#include "GameObject.h"
#include "Prefabs.h"
#include "WeaponComponent.h"
class Ship : public GameObject_Movable, public GameObject_WithHealth
{
public:
	Ship();
	Ship(const ShipPrefab * objectTemplate, const WeaponPrefab * weaponPrefab, Ogre::SceneManager * _sceneMenager );
	~Ship();
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
	void setWeapon(const WeaponPrefab * prefab){mWeapon.setWeapon(prefab);}
	unsigned getWeaponPrefabID() const { return mWeapon.getWeaponPrefabID(); }
	unsigned getBulletIDFromActiveWeapon() const {return mWeapon.getBulletID();}
	void setShip(const ShipPrefab * objectTemplate, const WeaponPrefab * weaponPrefab, Ogre::SceneManager * _sceneMenager ) 
	{
		setMesh(objectTemplate, _sceneMenager);
		setHealthAndColliderFromPrefab(objectTemplate);
		setPhysicsFromPrefab(objectTemplate);
		mWeapon.setWeapon(weaponPrefab);
	}

	virtual GameObjectType getType();

	virtual bool receiveDamage( unsigned int damages, Vector3 fromDirection = Vector3(0,0,0 ) );

private:  
	WeaponComponent mWeapon;
};

