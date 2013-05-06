#pragma once
#include "GameObject.h"
#include "Prefabs.h"
#include "WeaponComponent.h"
#include <vector>
class Ship : public GameObject_Movable, public GameObject_WithHealth
{
public:
	Ship();
	Ship(const ShipPrefab * objectTemplate, const WeaponPrefab * weaponPrefab, Ogre::SceneManager * _sceneMenager );
	~Ship();
	void setShoot(unsigned long currentTime)	{
		
		mActiveWeapon->setShoot(currentTime);
	}

	void unsetShoot()	{
		mActiveWeapon->unsetShoot();
	}

	bool isShooting()	{
		return mActiveWeapon->isShooting();
	}

	WeaponComponent& getCurrentWeapon()	{
		return *mActiveWeapon;
	}
	void setWeapon(const WeaponPrefab * prefab){mActiveWeapon->setWeapon(prefab);}
	unsigned getWeaponPrefabID() const { return mActiveWeapon->getWeaponPrefabID(); }
	unsigned getBulletIDFromActiveWeapon() const {return mActiveWeapon->getBulletID();}
	void setShip(const ShipPrefab * objectTemplate, const WeaponPrefab * weaponPrefab, Ogre::SceneManager * _sceneMenager ) 
	{
		setMesh(objectTemplate, _sceneMenager);
		setHealthAndColliderFromPrefab(objectTemplate);
		setPhysicsFromPrefab(objectTemplate);
		myWeapons[0].setWeapon(weaponPrefab);
		mActiveWeapon = &myWeapons[0];
		numerOfWeapons = 1;
		createThrusters(objectTemplate,_sceneMenager);
	}

	virtual GameObjectType getType();
	virtual bool receiveDamage( unsigned int damages, Vector3 fromDirection = Vector3(0,0,0 ) );
	
	void addWeapon(const WeaponPrefab * weaponPrefab);
	void changeWeaponTo(char weaponNumber);

private:  

	WeaponComponent * mActiveWeapon;
	vector<WeaponComponent> myWeapons;
	unsigned char numerOfWeapons;
};

