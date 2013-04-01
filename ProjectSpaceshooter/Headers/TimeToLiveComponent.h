#pragma once


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