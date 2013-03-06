#pragma once

#include "TransformComponent.h"
#include "GraphicsComponent.h"
#include "PhysicsComponent.h"
#include <string>
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
	GameObject();
	GameObject(std::string new_name);
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
	bool isShootActive() { return shoot;}
	void setShoot(bool _shoot) { shoot = _shoot;} 
	long int getTimeSinceLastShoot() {return timeSinceLastShoot;};
	void resetTimeSinceLastShoot() {timeSinceLastShoot = 0;};
	void incrementTimeSinceLastShoot(long int deltaTime) {timeSinceLastShoot += deltaTime;}
	std::string name;

private:
	GameObjectType mObjectType;
	TransformComponent mTransformComponent;
	GraphicsComponent mGraphicsComponent;
	PhysicsComponent mPhysicsComponent;
	long int timeSinceLastShoot;
	bool shoot;
};

