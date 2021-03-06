#pragma once

#include "AIStrategy.h"
#include "Exceptions.h"


/* AI mode where enemy is moving in random circles 
 * @author konkit
 */
class RandomAIStrategy : public AIStrategy {

public:
	virtual void update( EnemyObject* it, GameData& mGameData, TimeData time  )
	{
		PhysicsComponent& currentPhysicsComponent = it->getPhysicsComponent();

		//Check if EnemyObject even exists
		if( it == NULL )	{
			throw EnemyNullException();
		}


		//get some random values
		float currentVelocity  = float(200 + (rand()%300-100));
		float currentRotVelocity = float(0.4 + (rand()%50-25)/10);

		//set speed of enemy
		currentPhysicsComponent.setMaxVelocityValue(currentVelocity);
		//set its vector
		//currentPhysicsComponent.setVelocity(Ogre::Vector3(0.0, 0.0, 1.0));
		it->setTargetVelocityValue( 0.5 );
		//set it rotation speed
		currentPhysicsComponent.setTargetRotVelocity(currentRotVelocity);
	}
};
