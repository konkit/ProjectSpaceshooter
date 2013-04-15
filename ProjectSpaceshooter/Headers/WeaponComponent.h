#pragma once

class WeaponComponent {
public:
	WeaponComponent();

	WeaponComponent(int weaponPrefabID);
	void setWeapon(const WeaponPrefab * prefab);

	unsigned int getWeaponPrefabID() const { return weaponPrefabID; }
	void setWeaponPrefabID(unsigned int val) { weaponPrefabID = val; }

	/** sets shooting flag to true if time is proper */
	void setShoot(unsigned long currentTime);

	/** removes shooting flag (function run when shooting is happening */
	void unsetShoot();

	/** accessor function checking if shooting flag is set */
	bool isShooting();

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