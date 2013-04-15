#pragma once


class Collider	{

public:

//colider 
	Collider(const colider_struct & colider);
	Collider(const list<colider_struct> & colider_list);
	bool isCollidingOther( Ogre::Vector3 currentPos, Ogre::Vector3 otherPos, Collider & otherColider);

	bool isCollidingOther( Ogre::Vector3 currentPos, Ogre::Vector3 otherPos, float otherRadius);
	static bool isCollisionOccuring( Collider& coll1, Collider& coll2, Ogre::Vector3 pos1, Ogre::Vector3 pos2 );
	void addColider(colider_struct & _colider );
	const colider_struct & getFarthestColider( Vector3 offset ) const;
private:
	list<colider_struct> mColiders;
	// Here will be big colider sphere, which is enough big to cover all colider
	// It's to improve efficient 
	colider_struct inaccurateColider;
};
