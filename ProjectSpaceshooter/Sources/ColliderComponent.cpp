
bool Collider::isCollisionOccuring( Collider& coll1, Collider& coll2, Ogre::Vector3 pos1, Ogre::Vector3 pos2 )
{
	//calculate distance between positions
	float distance = (pos1 - pos2).length();

	//calculate sum of radii
	float radiiSum = coll1.mColiders.front().radian + coll2.mColiders.front().radian;

	//check which one is bigger and decide
	if( radiiSum < distance ) 
		return false;
	else
		return true;
}

bool Collider::isCollidingOther( Ogre::Vector3 currentPos, Ogre::Vector3 otherPos, float otherRadius )
{
	//calculate distance between positions
	float distance = 0;

	//calculate sum of radii
	float radiiSum = 0;

	//check which one is bigger and decide
	if( radiiSum > distance ) 
		return false;
	else
		return true;
}


Collider::Collider( const colider_struct & colider )
{
	mColiders.push_front(colider);
}

Collider::Collider( const list<colider_struct> & colider_list )
{
	mColiders = colider_list;
}

void Collider::addColider( colider_struct & _colider )
{
	static Vector3 lastMiddlePointSum(0.0f, 0.0f ,0.0f);
	static unsigned numberOfColiders = 0;
	//Square radian
	_colider.radian * _colider.radian;
	if (mColiders.empty())
	{
		inaccurateColider = _colider;
	} else
	{
		
		
	}
	mColiders.push_back = _colider;
}

const colider_struct & Collider::getFarthestColider( Vector3 offset ) const
{
	list<colider_struct>::const_iterator it;
	unsigned maxDistance;
	unsigned tmpDistance;
	colider_struct farthest;
	farthest = mColiders.front();
	tmpDistance = (farthest.offset -offset).squaredLength();
	for (it = ++mColiders.begin() ; it != mColiders.end(); it++)
	{
		tmpDistance = (it->offset -offset).squaredLength();
		if (tmpDistance + it->radian > maxDistance + farthest.radian)
		{
			farthest = *it;
			maxDistance = tmpDistance;
		}
	}
	return farthest;
}

