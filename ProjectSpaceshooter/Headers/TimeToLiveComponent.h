#pragma once

/** This component is part of game objects which exists in Game World
  * Only for a certain amount of time. 
  * This class governs counting time which is left for game object to live.
  *
  * @author konkit
  */
class TimeToLiveComponent
{
public:
	TimeToLiveComponent();

	/** sets the time after which object will be destroyed */
	void setTimeToLive(float newTime);

	/** function running every frame and decreasing time to live */
	void decreaseTimeToLive(float deltaTime);

	/** checks if time to destruction has left 
	* @return bool
	*/
	bool isTimeIsUp();

	/** Percentage of life time which left to die. Result as 0.## 
	* @return double
	* @author Zyga
	*/
	double percentOfLeftTime();
private:
	float timeToLive;
	float startTime;
};