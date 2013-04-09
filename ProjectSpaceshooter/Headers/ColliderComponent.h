#pragma once


class Collider	{

public:
	//sphere collider
	float radius;
//colider 
	Collider();

	bool isCollidingOther( Ogre::Vector3 currentPos, Ogre::Vector3 otherPos, float otherRadius );

	static bool isCollisionOccuring( Collider& coll1, Collider& coll2, Ogre::Vector3 pos1, Ogre::Vector3 pos2 );



private:
};
