#pragma once
#include "GameObject.h"
#include "Prefabs.h"
#include "WeaponComponent.h"
#include <vector>

/** Game object representing every ship - player ship or enemy ship
  * 
  * @author
  */
class Ship : public GameObject_Movable, public GameObject_WithHealth
{
public:
	/** Sets initial values */
	Ship();
	/** Loads data of effect from prefab */
	Ship(const ShipPrefab * objectTemplate, const WeaponPrefab * weaponPrefab, Ogre::SceneManager * _sceneMenager );
	~Ship();

	/** Sets ship shooting flag to true
	  * if shot is possible, than it is realised. If not, then nothing happens 
	  */
	void setShoot(unsigned long currentTime)	{		
		mActiveWeapon->setShoot(currentTime);
	}

	/** Sets shoot flag to false. Called when bullet is created in objectstateupdate system
	  */
	void unsetShoot()	{
		mActiveWeapon->unsetShoot();
	}

	/** checks if ship is currently shooting
	  * @return bool - true when ship is shooting 
	  */
	bool isShooting()	{
		return mActiveWeapon->isShooting();
	}

	WeaponComponent& getCurrentWeapon()	{
		return *mActiveWeapon;
	}

	// weapon settings methods
	void setWeapon(const WeaponPrefab * prefab){mActiveWeapon->setWeapon(prefab);}
	unsigned getWeaponPrefabID() const { return mActiveWeapon->getWeaponPrefabID(); }
	unsigned getBulletIDFromActiveWeapon() const {return mActiveWeapon->getBulletID();}
	void addWeapon(const WeaponPrefab * weaponPrefab);
	void changeWeaponTo(char weaponNumber);

	/** This method sets ship data from prefab	  */
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

	/** implementation of getType virtual method from GameObject class */
	virtual GameObjectType getType();

	virtual bool receiveDamage( unsigned int damages, Vector3 fromDirection = Vector3(0,0,0 ) );
	
	

private:  

	WeaponComponent * mActiveWeapon;
	vector<WeaponComponent> myWeapons;
	unsigned char numerOfWeapons;
};

