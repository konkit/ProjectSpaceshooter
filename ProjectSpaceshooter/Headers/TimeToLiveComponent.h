#pragma once


class TimeToLiveComponent
{
public:
	TimeToLiveComponent() {}

	void setTimeToLive(int newTime)	{
		timeToLive = newTime;
	}

	/** function running every frame and decreasing time to live */
	void decreaseTimeToLive()	{
		timeToLive--;
	}

	bool isTimeIsUp()	{
		return timeToLive<0;
	}
private:
	int timeToLive;
};