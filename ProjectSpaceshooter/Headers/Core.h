#pragma once

#include "StaticObject.h"

class Core : public StaticObject
{
public:
	Core() : GameObject()
	{

	}
	Core(const PrefabWithCollider * prefab, Ogre::SceneManager* sceneMgr)
		: GameObject(prefab, sceneMgr), StaticObject(prefab, sceneMgr)
	{

	}
	GameObjectType getType() {
		return GameObjectType::core;
	}
	virtual ~Core() {;}
private:


};