#pragma once

#include "StaticObject.h"

class Core : public StaticObject
{
public:
	Core() : GameObject()
	{

	}
	Core(const PrefabWithColider * prefab, Ogre::SceneManager* sceneMgr)
		: StaticObject(prefab, sceneMgr)
	{

	}
	GameObjectType getType() {
		return GameObjectType::core;
	}

private:


};