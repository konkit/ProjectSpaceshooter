#pragma once

class WeaponComponent {
public:
	WeaponComponent();

	WeaponComponent(float power);

	void setPower(float newPower);
	float getPower();

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
	unsigned long timeSinceLastShot;
	float mPower;
};