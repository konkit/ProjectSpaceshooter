#pragma once




class GamelogicComponent
{
public:
	GamelogicComponent() : shooting(false), rateOfFire(500), timeSinceLastShot(0), timeToLive(1000)
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

	void setTimeToLive(int newTime)	{
		timeToLive = newTime;
	}

	void decreaseTimeToLive()	{
		timeToLive--;
	}

	bool isStillAlive()	{
		return timeToLive > 0;
	}




private:
	bool shooting;
	//weapon data
	int rateOfFire;
	//time last shot
	unsigned long timeSinceLastShot;

	int timeToLive;

	
};