#pragma once
#include "GameObject.h"
class GameObjectFactory
{
	GameObjectFactory(){};
	~GameObjectFactory(void){};
public:
	static GameObject * getGameObject(GameObjectType newObjectType);
};
