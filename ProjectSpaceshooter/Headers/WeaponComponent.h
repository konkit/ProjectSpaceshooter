#pragma once

class WeaponComponent {
public:
	WeaponComponent() : shooting(false), rateOfFire(150), timeSinceLastShot(0) 
	{}

	WeaponComponent(float power) : mPower(power), shooting(false), rateOfFire(150), timeSinceLastShot(0)
	{}

	void setPower(float newPower)	{ mPower = newPower; }
	float getPower() { return mPower; }

	/** sets shooting flag to true if time is proper */
	void setShoot(unsigned long currentTime)	{
		if( timeSinceLastShot + rateOfFire < currentTime )	{
			shooting = true;
			timeSinceLastShot = currentTime;
		}
	}

	/** removes shooting flag (function run when shooting is happening */
	void unsetShoot()	{
		shooting = false;
	}

	/** accessor function checking if shooting flag is set */
	bool isShooting()	{
		return shooting;
	}

private:


	//flags
	bool shooting;

	//weapon data
	int rateOfFire;
	unsigned long timeSinceLastShot;
	float mPower;
};