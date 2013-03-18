#pragma once



/**Component which saves information needed to create or destroy objects
 * shooting - flag set when object is shooting - bullet is needed to be created
 * rateOfFire - rate on which object can shoot
 * timeSinceLastShot - time value needed to know if object is allowed to shoot since previous shot
 * timeToLive - time value (currently - number of frames) until object is deleted
 * 
 * @author konkit
 */

class GamelogicComponent
{
public:
	GamelogicComponent() : shooting(false), rateOfFire(500), timeSinceLastShot(0), timeToLive(1000)
	{	}

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

	/** sets time after which object will be deleted
	  * currently this time is number of frames */
	void setTimeToLive(int newTime)	{
		timeToLive = newTime;
	}

	/** function running every frame and decreasing time to live */
	void decreaseTimeToLive()	{
		timeToLive--;
	}

	bool isStillAlive()	{
		return timeToLive > 0;
	}




private:
	//flags
	bool shooting;

	//weapon data
	int rateOfFire;
	unsigned long timeSinceLastShot;

	//lifetime management
	int timeToLive;

	
};