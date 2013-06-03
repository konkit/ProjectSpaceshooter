#pragma once

/**  
 * Component storing data about current weapon
 * @author konkit
 */
class WeaponComponent {
public:
	/**
	 * 
	 *
	 * @author konkit
	 */
	WeaponComponent();
	/**
	 * Save weapon prefab id but don't initialize bullet, it require to call setWeapon with right prefab.
	 * @param weaponPrefabID weapon prefab id
	 * @author Zyga
	 */
	WeaponComponent(int weaponPrefabID);
	/**
	 * Constructor building weapon component based on prefab
	 * @param prefab weapon prefab storing information about weapon
	 * @author Zyga
	 */
	WeaponComponent(const WeaponPrefab * prefab);
	
	/**
	 * Method building weapon component based on prefab/
	 * @param prefab weapon prefab storing information about weapon
	 * @author Zyga
	 */
	void setWeapon(const WeaponPrefab * prefab);

	/**
	 * This method is use full when we construct weapon with ID, 
	 * and we need that id to get weapon prefab from gameData to initialize this component
	 * @return weapon Prefab ID
	 * @author Zyga
	 */
	unsigned int getWeaponPrefabID() const { return weaponPrefabID; }

	/**
	 * Accessor to set weapon prefab OD
	 * @param val Set weapon prefab.
	 * @author Zyga
	 */
	void setWeaponPrefabID(unsigned int val) { weaponPrefabID = val; }

	/**
	 * sets shooting flag to true if time is proper
	 * @param currentTime 
	 * @author konkit
	 */
	void setShoot(unsigned long currentTime);

	/**
	 * removes shooting flag (function run when shooting is happening
	 * @author konkit
	 */
	void unsetShoot();

	/**
	 * Accessor function checking if shooting flag is set 
	 * @return If shooting flag is set return true.
	 * @author konkit
	 */
	bool isShooting();

	/**
	 * @return ID Bullet prefab which this component shoot.
	 * @author Zyga
	 */
	unsigned getBulletID() const {return bulletPrefabID;}

private:
	//flags
	bool shooting;
	//weapon data
	int rateOfFire;
	string weaponName;
	unsigned long timeSinceLastShot;
	unsigned int weaponPrefabID;
	unsigned int bulletPrefabID;
};