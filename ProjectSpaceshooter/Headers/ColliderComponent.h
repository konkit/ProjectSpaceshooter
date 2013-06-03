#pragma once
#include <list>
#include "OgreVector3.h"
#include "OgreQuaternion.h"


using Ogre::Vector3;
using namespace std;


/**
 * Structure used in collider component which stores information about single collider offset and radius
 * @author Zyga
 */
struct Collider_struct
{
	Vector3			offset;
	unsigned		radius;
	Collider_struct()
		: radius(0), offset(0.0, 0.0, 0.0) {}
};

/**
 * Structure stores information about position: position vector and orientation in quaternion
 * @author Zyga
 */
struct position_struct
{
	Vector3 position;
	Ogre::Quaternion orientation;
	position_struct() : position(0,0,0), orientation(){;}
};

/**
 * Collider component stores data about collider which game object has.
 * To provide good accuracy, collider can be build from number of small spheres, 
 * but to provide collider's high efficiency, it is required to set inaccurate collider which should cover all small collider.
 * Small collider will be checked only when there is inaccurate collision.
 * If there is less then two small colliders, only inaccurate collisions will be checked.
 * @author Zyga
 */
class Collider	{

public:
	/**
	* Collider constructor which make empty colider component
	* @author Zyga
	*/
	Collider();

	/**
	* Clear collider list
	* @author Zyga
	*/
	~Collider() {mColliders.clear();}
	/**
	* Method which check if there are collision between two single collider sphere
	* @return bool return true if there is collision between spheres
	* @param const Collider_struct & coll1 first collider sphere
	* @param const position_struct pos1 first sphere offset
	* @param const Collider_struct & coll2 second collider sphere
	* @param const position_struct & pos2 second sphere offset
	* @author Zyga
	*/
	static bool isCollisionOccuring(const Collider_struct& coll1, const position_struct pos1, const Collider_struct& coll2, const position_struct& pos2 );
	
	/** 
	* Add colliding sphere to collider component, it will be treat like a small collider
	* @param Collider_struct & _Collider
	* @author Zyga
	*/
	void addCollider(Collider_struct & _Collider ) {mColliders.push_back(_Collider);} 

	/**
	* Set inaccurate collider. It is important to check collision,
	* because collision is check only when there is inaccurate collision 
	* @param Collider_struct & _Collider structure which describe collider sphere
	* @author Zyga
	*/
	void setInaccurateCollider(Collider_struct & _Collider) {inaccurateCollider = _Collider;}

	/**
	* @author Zyga
	*/
	const Collider_struct & getInaccurateCollider() const {return inaccurateCollider;}

	/**
	* @return list<Collider_struct>::const_iterator return collider list iterator begin
	* @author Zyga
	*/
	list<Collider_struct>::const_iterator inline getCollidersBegin() const {return mColliders.begin();}

	/**
	* @return list<Collider_struct>::const_iterator return collider list iterator end
	* @author Zyga
	*/
	list<Collider_struct>::const_iterator inline getCollidersEnd() const {return mColliders.end();}
	/**
	* Method check if there is collision between two collider component
	* @return bool return true if there is collision between this and other collider
	* @param const position_struct & currentPos this collider component position
	* @param const Collider & otherCollider other collider component position
	* @param const position_struct & otherPos other collider
	* @author Zyga
	*/
	bool isCollidingWith(const position_struct& currentPos, const Collider& otherCollider,const position_struct & otherPos);

	/**
	* Clear collider component.
	* @author Zyga
	*/
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
