#pragma once

#include "TransformComponent.h"
#include "GraphicsComponent.h"
#include "PhysicsComponent.h"

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

	GraphicsComponent& getGraphicsComponent()	{
		return mGraphicsComponent;
	}

	PhysicsComponent& getPhysicsComponent()	{
		return mPhysicsComponent;
	}



private:
	GameObjectType mObjectType;
	TransformComponent mTransformComponent;
	GraphicsComponent mGraphicsComponent;
	PhysicsComponent mPhysicsComponent;
};

