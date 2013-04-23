#pragma once
#include "Prefabs.h"

class StaticObject : public GameObject_WithHealth
{
public:
	StaticObject(void);
	StaticObject(const PrefabWithColider * prefab, Ogre::SceneManager* sceneMgr)
		: GameObject(prefab, sceneMgr), GameObject_WithHealth(prefab, sceneMgr)
	{
	}
	~StaticObject(void);
};

