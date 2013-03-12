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

		GameObjectsCollectionIterator<GameObject> * myIterator = mGameData.getBullets().getIterator();
		GameObject* it;
		while (myIterator->hasNext())
		{
			it = myIterator->getNext();
			//for every game object
			PhysicsComponent& tmpPhysics = 
				it->getPhysicsComponent();
			TransformComponent& tmpTransform = 
				it->getTransformComponent();

			tmpTransform.rotate( tmpPhysics.getRotVelocity() * deltaTime );
			tmpTransform.move( tmpPhysics.getVelocity() * deltaTime );
		}
		delete myIterator;
	}


private:

};