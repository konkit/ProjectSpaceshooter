#pragma once
#include "Prefabs.h"

using namespace std;

/** Just static, not movable gameobject
  * It has health component so it can be destroyed
  *
  * @author
  */
class StaticObject : public GameObject_WithHealth
{
public:
	/** Sets initial values */
	StaticObject(void);

	/** Loads data of effect from prefab */
	StaticObject(const PrefabWithCollider * prefab, Ogre::SceneManager* sceneMgr)
		: GameObject(prefab, sceneMgr), GameObject_WithHealth(prefab, sceneMgr)
	{	}

	~StaticObject(void);

	/** implementation of getType virtual method from GameObject class */
	virtual GameObjectType getType() {return GameObjectType::staticObject;}
};

