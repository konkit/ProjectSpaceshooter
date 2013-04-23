#pragma once
#include "Prefabs.h"

class StaticObject : public GameObject_WithHealth
{
public:
	StaticObject(void);
	StaticObject(const PrefabWithCollider * prefab, Ogre::SceneManager* sceneMgr)
		: GameObject(prefab, sceneMgr), GameObject_WithHealth(prefab, sceneMgr)
	{
	}
	~StaticObject(void);

	virtual GameObjectType getType() {return GameObjectType::staticObject;}

};

