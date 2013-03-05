#pragma once

#include "GameData.h"

class PhysicsSystem
{
public:
	void update(GameData& mGameData)
	{
		//for every game object
		PhysicsComponent& tmpPhysics = 
			mGameData.getPlayer()->getPhysicsComponent();
		TransformComponent& tmpTransform = 
			mGameData.getPlayer()->getTransformComponent();

		tmpTransform.rotate( tmpPhysics.rotVelocity );
		tmpTransform.move(tmpPhysics.velocityX, 
							tmpPhysics.velocityY,
							tmpPhysics.velocityZ);

	}


private:

};