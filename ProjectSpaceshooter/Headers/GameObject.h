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


	bool isShootActive() { return shoot;}
	void setShoot(bool _shoot) { shoot = _shoot;} 
	long int getTimeSinceLastShoot() {return timeSinceLastShoot;};
	void resetTimeSinceLastShoot() {timeSinceLastShoot = 0;};
	void incrementTimeSinceLastShoot(long int deltaTime) {timeSinceLastShoot += deltaTime;}

	void setShoot(unsigned long currentTime)	{
		mGamelogicComponent.setShoot(currentTime);
	}

	void unsetShoot()	{
		mGamelogicComponent.unsetShoot();
	}

	bool isShooting()	{
		return mGamelogicComponent.isShooting();
	}




protected:
	GameObjectType mObjectType;
	TransformComponent mTransformComponent;
	GraphicsComponent mGraphicsComponent;
	PhysicsComponent mPhysicsComponent;
	GamelogicComponent mGamelogicComponent;
	long int timeSinceLastShoot;
	bool shoot;


};

