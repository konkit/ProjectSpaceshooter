#pragma once
#include <list>
#include "OgreVector3.h"
#include "OgreQuaternion.h"


using Ogre::Vector3;
using namespace std;
/** Collider component stores data about collider which game object has
  * 
  * @author konkit
  */


struct Collider_struct
{
	Vector3			offset;
	unsigned		radius;
	Collider_struct()
		: radius(0), offset(0.0, 0.0, 0.0) {}
};


struct position_struct
{
	Vector3 position;
	Ogre::Quaternion orientation;
	position_struct() : position(0,0,0), orientation(){;}
};
class Collider
{

public:

//Collider 
	Collider();
	static bool isCollisionOccuring(const Collider_struct& coll1, const position_struct pos1, const Collider_struct& coll2, const position_struct& pos2 );
	void addCollider(Collider_struct & _Collider ) {mColliders.push_back(_Collider);} 
	void setInaccurateCollider(Collider_struct & _Collider) {inaccurateCollider = _Collider;}
	const Collider_struct & getInaccurateCollider() const {return inaccurateCollider;}

	list<Collider_struct>::const_iterator inline getCollidersBegin() const {return mColliders.begin();}
	list<Collider_struct>::const_iterator inline getCollidersEnd() const {return mColliders.end();}
	bool isCollidingWith(const position_struct& currentPos, const Collider& otherCollider,const position_struct & otherPos);

	void reset() 
	{
		inaccurateCollider.offset = Vector3(0,0,0);
		inaccurateCollider.radius = 0;
		mColliders.clear();
	};
private:
	bool inline checkInaccurateColliders( const position_struct& currentPos,const Collider& otherCollider, const position_struct& otherPos );
	bool inline checkColisionOnColliderList( const position_struct& currentPos,const Collider& otherCollider, const position_struct& otherPos );
	list<Collider_struct> mColliders;
	
	// Here will be big Collider sphere, which is enough big to cover all Collider
	// It's to improve efficient 
	Collider_struct inaccurateCollider;
};
