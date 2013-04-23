#pragma once

#include "DebugDrawer.h"

//#define ALLColliderS true

class CollisionSystem	{
public:
	//Method which resolves collisions
	//collisions are resolved a posteriori
	void update(GameData& mGameData)	
	{
		GameData::ColidingObjectsIterator it = mGameData.getColidingObjectsIterator();
		GameObject_WithCollider * obj;
		Collider_struct coli;
		position_struct pos;

		while (it.hasNext())
		{
			obj = it.getNext();
			CheckForCollisions(obj, it ,mGameData);
#ifdef _DEBUG
			//Collider _Collider	= obj->getCollider();
			//coli = _Collider.getInaccurateCollider();
			coli = obj->getCollider().getInaccurateCollider();
			pos = obj->getPositionAndOrientation();
			coli.offset = (pos.orientation * coli.offset) + pos.position;
			DebugDrawer::getSingleton().drawCircle(coli.offset, coli.radius, 25, Ogre::ColourValue(1.0f, 1.0f, 1.0f) );

#ifdef ALLColliderS
			list<Collider_struct>::const_iterator coli_IT = _Collider.getCollidersBegin();
			list<Collider_struct>::const_iterator coli_end = _Collider.getCollidersEnd();
			
			for ( ; coli_IT != coli_end; coli_IT++)
			{
			coli = *coli_IT;
			pos = obj->getPositionAndOrientation();
			coli.offset = (pos.orientation * coli.offset) + pos.position;
			DebugDrawer::getSingleton().drawCircle(coli.offset, coli.radius, 25, Ogre::ColourValue(1.0f, 0.0f, 0.0f) );
			}
#endif // ALLColliderS

#endif 
		}
	}

	void CheckForCollisions( GameObject_WithCollider * currentObject, GameData::ColidingObjectsIterator it ,GameData& mGameData)	
	{	
		GameObject_WithCollider * tmp;
		while(it.hasNext())
		{
			tmp = it.getNext();
			if (tmp != currentObject)
			{
				if (currentObject->isColidingWith(tmp))
				{
					currentObject->hit(tmp);
					tmp->hit(currentObject);
					std::cout << "Collision detected\n";
				}
			}
		}

	}

private:

};
