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

	void setTimeToLive(int newTime);

	/** function running every frame and decreasing time to live */
	void decreaseTimeToLive();

	bool isTimeIsUp();
private:
	int timeToLive;
};