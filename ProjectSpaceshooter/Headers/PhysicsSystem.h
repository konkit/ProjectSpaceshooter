#pragma once

#include "GameData.h"


/** 
  * System governing physics stuff (velocities, accelerations etc)
  * @author konkit
  */
class PhysicsSystem
{
public:

	/** update function running for every frame 
	  * @param mGameData - GameData paramter - there are all GameObject data
	  * @param deltaTime - time since last frame - needed in physics calculations 
	  */
	void update(GameData& mGameData, float deltaTime)
	{
		//player object update
		PhysicsComponent& tmpPhysics = 
			mGameData.getPlayer()->getPhysicsComponent();
		GraphicsComponent& tmpGraphics = 
			mGameData.getPlayer()->getGraphicsComponent();

		tmpGraphics.rotate( tmpPhysics.getRotVelocity() * deltaTime );
		tmpGraphics.move( tmpPhysics.getVelocity() * deltaTime );

		//bullet objects update
		GameCollectionIterator<Bullet> * myIterator = mGameData.getBullets().getBulletIterator();
		GameObject* it;
		while (myIterator->hasNext())
		{
			it = myIterator->getNext();
			//for every game object
			PhysicsComponent& tmpPhysics = 
				it->getPhysicsComponent();
			GraphicsComponent& tmpGraphics = 
				it->getGraphicsComponent();

			tmpGraphics.rotate( tmpPhysics.getRotVelocity() * deltaTime );
			tmpGraphics.move( tmpPhysics.getVelocity() * deltaTime );
		}
		delete myIterator;
	}


private:

};