//#include "ColliderComponent.h"
#pragma once
#include "./../Headers/ColliderComponent.h"
Collider::Collider()
{

}

bool Collider::isCollisionOccuring(const Collider_struct& coll1, const position_struct pos1, const Collider_struct& coll2, const position_struct& pos2 )
{
	Vector3 _pos1 = (pos1.orientation * coll1.offset) + pos1.position;
	Vector3 _pos2 = (pos2.orientation * coll2.offset) + pos2.position;
	Vector3 tmp = _pos2 - _pos1;
	Ogre::Real distance = tmp.squaredLength();
	Ogre::Real radiusSum = coll1.radius + coll2.radius;
	radiusSum *= radiusSum;
	if (radiusSum > distance)
	{
		return true;
	} else
	{
		return false;
	}

}

bool Collider::isCollidingWith( const position_struct& currentPos, const Collider& otherCollider,const position_struct & otherPos )
{	
	if(checkInaccurateColliders(currentPos, otherCollider, otherPos))
		return checkColisionOnColliderList(currentPos, otherCollider, otherPos);
	else
		return false;
}

bool inline Collider::checkInaccurateColliders( const position_struct& currentPos,const Collider& otherCollider, const position_struct& otherPos )
{
	return isCollisionOccuring(inaccurateCollider, currentPos, otherCollider.getInaccurateCollider(), otherPos);
}

bool inline Collider::checkColisionOnColliderList( const position_struct& currentPos,const Collider& otherCollider, const position_struct& otherPos )
{
	list<Collider_struct>::const_iterator my_it, oth_it;
	list<Collider_struct>::const_iterator oth_it_begin = otherCollider.getCollidersBegin();
	list<Collider_struct>::const_iterator oth_it_end = otherCollider.getCollidersEnd();

	for (my_it = mColliders.begin(); my_it != mColliders.end(); my_it++)
	{
		for (oth_it = oth_it_begin; oth_it != oth_it_end; oth_it++)
		{ 
			if (isCollisionOccuring(*my_it, currentPos, *oth_it, otherPos))
			{
				return true;
			}
		}
	}
	return false;
}


