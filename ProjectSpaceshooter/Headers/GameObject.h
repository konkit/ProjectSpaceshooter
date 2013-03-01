#pragma once

#include "TransformComponent.h"

enum  class GameObjectType 
{
	player,
	enemyObject,
	bulletObject,
	staticObject,
	physicObject
};

class GameObject 
{
public:
	GameObject(GameObjectType newObjectType);
	virtual ~GameObject(void);

	TransformComponent& getTransformComponent()	{
		return mTransformComponent;
	}


private:
	GameObjectType mObjectType;
	TransformComponent mTransformComponent;
};

