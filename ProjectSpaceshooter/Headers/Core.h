#pragma once

#include "StaticObject.h"

/** Core game object - this object needs to be defended by player
  * It's just special instance of StaticObject
  *
  * @author 
  */
class Core : public StaticObject
{
public:
	/** Sets initial values */
	Core() : GameObject()
	{	}

	/** Loads data of effect from prefab */
	Core(const PrefabWithCollider * prefab, Ogre::SceneManager* sceneMgr)
		: GameObject(prefab, sceneMgr), StaticObject(prefab, sceneMgr)
	{	}

	/** implementation of getType virtual method from GameObject class */
	GameObjectType getType() {
		return GameObjectType::core;
	}

	/** virtual destructor of the core */
	virtual ~Core() {;}

	friend ostream& operator<< ( ostream & stream, Core& object)	{
		return stream<<"Core ("<<object.getPosition()<<") ";
	}
};