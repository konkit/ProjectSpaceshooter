#pragma once

#include "DebugDrawer.h"

//#define ALLCOLIDERS true

class CollisionSystem	{
public:
	//Method which resolves collisions
	//collisions are resolved a posteriori
	void update(GameData& mGameData)	
	{
		GameData::ColidingObjectsIterator it = mGameData.getColidingObjectsIterator();
		GameObject_WithColider * obj;
		colider_struct coli;
		position_struct pos;

		while (it.hasNext())
		{
			obj = it.getNext();
			CheckForCollisions(obj, it ,mGameData);
#ifdef _DEBUG
			//Collider _colider	= obj->getColider();
			//coli = _colider.getInaccurateColider();
			coli = obj->getColider().getInaccurateColider();
			pos = obj->getPositionAndOrientation();
			coli.offset = (pos.orientation * coli.offset) + pos.position;
			DebugDrawer::getSingleton().drawCircle(coli.offset, coli.radius, 25, Ogre::ColourValue(1.0f, 1.0f, 1.0f) );

#ifdef ALLCOLIDERS
			list<colider_struct>::const_iterator coli_IT = _colider.getColidersBegin();
			list<colider_struct>::const_iterator coli_end = _colider.getColidersEnd();
			
			for ( ; coli_IT != coli_end; coli_IT++)
			{
			coli = *coli_IT;
			pos = obj->getPositionAndOrientation();
			coli.offset = (pos.orientation * coli.offset) + pos.position;
			DebugDrawer::getSingleton().drawCircle(coli.offset, coli.radius, 25, Ogre::ColourValue(1.0f, 0.0f, 0.0f) );
			}
#endif // ALLCOLIDERS

#endif 
		}
	}

	void CheckForCollisions( GameObject_WithColider * currentObject, GameData::ColidingObjectsIterator it ,GameData& mGameData)	
	{	
		GameObject_WithColider * tmp;
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
