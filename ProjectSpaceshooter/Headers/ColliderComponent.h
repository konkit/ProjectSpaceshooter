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

class Collider	{

struct colider_struct
{
	Vector3			offset;
	unsigned		radius;
	colider_struct()
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

//colider 
	Collider();
	static bool isCollisionOccuring(const colider_struct& coll1, const position_struct pos1, const colider_struct& coll2, const position_struct& pos2 );
	void addColider(colider_struct & _colider ) {mColiders.push_back(_colider);} 
	void setInaccurateColider(colider_struct & _colider) {inaccurateColider = _colider;}
	const colider_struct & getInaccurateColider() const {return inaccurateColider;}

	list<colider_struct>::const_iterator inline getColidersBegin() const {return mColiders.begin();}
	list<colider_struct>::const_iterator inline getColidersEnd() const {return mColiders.end();}
	bool isCollidingWith(const position_struct& currentPos, const Collider& otherColider,const position_struct & otherPos);

	void reset() 
	{
		inaccurateColider.offset = Vector3(0,0,0);
		inaccurateColider.radius = 0;
		mColiders.clear();
	};
private:
	bool inline checkInaccurateColiders( const position_struct& currentPos,const Collider& otherColider, const position_struct& otherPos );
	bool inline checkColisionOnColiderList( const position_struct& currentPos,const Collider& otherColider, const position_struct& otherPos );
	list<colider_struct> mColiders;
	
	// Here will be big colider sphere, which is enough big to cover all colider
	// It's to improve efficient 
	colider_struct inaccurateColider;
};
