#pragma once

#include "TransformComponent.h"
#include "GraphicsComponent.h"
#include "PhysicsComponent.h"
#include "GamelogicComponent.h"
#include <string>
enum  class GameObjectType 
{
	player,
	enemyObject,
	bulletObject,
	staticObject,
	physicObject
};

enum class AI_TYPE
{
	fighter,
	defender
};

/** Game object class
  * Game objects represents object in gameworld - enemies, bullets etc.
  * Those are composed from components (physics component, gamelogiccomponent, etc.)
  * This is abstract class - Bullet, Enemy and other classes inherit from this class
  * 
  * @author 
  */
class GameObject 
{
public:
	GameObject();
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

	GamelogicComponent& getGamelogicComponent() {
		return mGamelogicComponent;
	}

protected:
	GameObjectType mObjectType;
	TransformComponent mTransformComponent;
	GraphicsComponent mGraphicsComponent;
	PhysicsComponent mPhysicsComponent;
	GamelogicComponent mGamelogicComponent;


};

