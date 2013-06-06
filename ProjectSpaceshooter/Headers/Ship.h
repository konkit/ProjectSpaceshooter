#pragma once
#include "GameObject.h"
#include "Prefabs.h"
#include "WeaponComponent.h"
#include <vector>

/** Game object representing every ship - player ship or enemy ship
  * 
  * @author Zyga
  */
class Ship : public GameObject_Movable, public GameObject_WithHealth
{
public:
	/** Sets initial values */
	Ship();

	/** Loads data of effect from prefab 
	  * @param objectTemplate - object with data of this ship
	  * @param weaponPrefab - object with data of weapons
	  * @param _sceneManager - sceneManager which this game object belongs
	  */
	Ship(const ShipPrefab * objectTemplate, const WeaponPrefab * weaponPrefab, Ogre::SceneManager * _sceneMenager );

	~Ship();

	/** Sets ship shooting flag to true
	  * if shot is possible, than it is realised. If not, then nothing happens 
	  * @param currentTime - time in miliseconds since program started
	  * @author konkit
	  */
	void setShoot(unsigned long currentTime)	{		
		mActiveWeapon->setShoot(currentTime);
	}

	/** Sets shoot flag to false. Called when bullet is created in objectstateupdate system
	  * @author konkit
	  */
	void unsetShoot()	{
		mActiveWeapon->unsetShoot();
	}

	/** checks if ship is currently shooting
	  * @author konkit
	  * @return bool - true when ship is shooting 
	  */
	bool isShooting()	{
		return mActiveWeapon->isShooting();
	}

	/** returns currently chosen weapon
	  * @author konkit
	  * @return active weapon
	  */
	WeaponComponent& getCurrentWeapon()	{
		return *mActiveWeapon;
	}

	// weapon settings methods

	/** returns currently chosen weapon
	  * @return active weapon
	  */
	void setWeapon(const WeaponPrefab * prefab){mActiveWeapon->setWeapon(prefab);}

	/** returns currently chosen weapon
	  * @return active weapon
	  */
	unsigned getWeaponPrefabID() const { return mActiveWeapon->getWeaponPrefabID(); }

	/** returns currently chosen weapon
	  * @return active weapon
	  */
	unsigned getBulletIDFromActiveWeapon() const {return mActiveWeapon->getBulletID();}

	/** returns currently chosen weapon
	  * @return active weapon
	  */
	void addWeapon(const WeaponPrefab * weaponPrefab);

	/** returns currently chosen weapon
	  * @return active weapon
	  */
	void changeWeaponTo(char weaponNumber);

	/** This method sets ship data from prefab	  
	  * @param objectTemplate - object with data of this ship
	  * @param weaponPrefab - object with data of weapons
	  * @param _sceneManager - sceneManager which this game object belongs
	  */
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

