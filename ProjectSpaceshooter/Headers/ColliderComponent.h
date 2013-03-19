#pragma once


class Collider	{

public:
	//sphere collider
	float radius;

	Collider() : radius(4.0f) {}

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

	static bool isCollisionOccuring( Collider& coll1, Collider& coll2, Ogre::Vector3 pos1, Ogre::Vector3 pos2 )	
	{
		//calculate distance between positions
		float distance = (pos1 - pos2).length();

		//calculate sum of radii
		float radiiSum = coll1.radius + coll2.radius;

		//check which one is bigger and decide
		if( radiiSum < distance ) 
			return false;
		else
			return true;
	}



private:
};
