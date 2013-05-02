#pragma once

#include "GameData.h"

#ifdef _DEBUG
#include "DebugDrawer.h"
#endif

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
		updateOneObject( mGameData.getPlayer(), deltaTime );

		//bullet objects update
		GameCollectionIterator<Bullet> myIterator = mGameData.getBullets().getIterator();
		GameObject_Movable* it;
		while (myIterator.hasNext())
		{
			it = myIterator.getNext();
			//for every game object
			updateOneObject(it, deltaTime);
		}

		GameCollectionIterator<EnemyObject> myEnemyIterator = mGameData.getEnemies().getIterator();
		while (myEnemyIterator.hasNext())
		{
			it = myEnemyIterator.getNext();
			//for every game object
			updateOneObject(it, deltaTime);
		}
	}

	void updateOneObject( GameObject_Movable* it, float deltaTime ) {
		if (it == NULL) //TODO
		{
			return;
		}
		PhysicsComponent& tmpPhysics = it->getPhysicsComponent();

		tmpPhysics.updateVelocity();

		it->rotate( tmpPhysics.getRotVelocity() * deltaTime );
		it->move( tmpPhysics.getCurrentVelocity() * deltaTime );

#ifdef _DEBUG
		DebugDrawer::getSingleton().drawLine( it->getPosition(), it->getPosition()+tmpPhysics.getTargetVelocity(), Ogre::ColourValue(1.0, 1.0, 0.0, 0.0 ));
		DebugDrawer::getSingleton().drawLine( it->getPosition(), it->getPosition()+tmpPhysics.getCurrentVelocity(), Ogre::ColourValue(1.0, 1.0, 0.0, 0.0 ));
#endif 
	}


private:

};