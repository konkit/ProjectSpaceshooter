#pragma once

#include "GameData.h"

class PhysicsSystem
{
public:
	void update(GameData& mGameData, float deltaTime)
	{
		//for every game object
		PhysicsComponent& tmpPhysics = 
			mGameData.getPlayer()->getPhysicsComponent();
		TransformComponent& tmpTransform = 
			mGameData.getPlayer()->getTransformComponent();

		tmpTransform.rotate( tmpPhysics.getRotVelocity() * deltaTime );
		tmpTransform.move( tmpPhysics.getVelocity() * deltaTime );
	}


private:

};