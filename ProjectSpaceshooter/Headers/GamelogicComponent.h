#pragma once


enum class ActivityType { 
	passive,
	shoot 
};



class GamelogicComponent
{
	void setActivity(ActivityType activity)	{
		currentActivity = activity;
	}

	ActivityType getActivity()	{
		return currentActivity;
	}



private:
	//current action
	ActivityType currentActivity;

	//weapon data
	float rateOfFire;
	//time last shot

	
};