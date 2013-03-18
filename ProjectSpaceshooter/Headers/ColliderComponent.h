#pragma once


class Collider	{

public:
	//sphere collider
	float radius;

	bool isCollidingOther( Ogre::Vector3 currentPos, Ogre::Vector3 otherPos, float otherRadius )	{
		//calculate distance between positions
		float distance;

		//calculate sum of radii
		float radiiSum;

		//check which one is bigger and decide
		if( radiiSum > distance ) 
			return false;
		else
			return true;
	}



private:
};
