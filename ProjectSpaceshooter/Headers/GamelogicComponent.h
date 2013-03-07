#pragma once




class GamelogicComponent
{
public:
	GamelogicComponent() : shooting(false), rateOfFire(500), timeSinceLastShot(0)
	{	}

	void setShoot(unsigned long currentTime)	{
		if( timeSinceLastShot + rateOfFire < currentTime )	{
			shooting = true;
			timeSinceLastShot = currentTime;
		}
	}

	void unsetShoot()	{
		shooting = false;
	}

	bool isShooting()	{
		return shooting;
	}




private:
	bool shooting;
	//weapon data
	int rateOfFire;
	//time last shot
	unsigned long timeSinceLastShot;

	
};