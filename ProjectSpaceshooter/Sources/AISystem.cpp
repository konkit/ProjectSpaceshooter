#include "AISystem.h"

#include <cmath>

void AISystem::update( GameData& mGameData, TimeData time )
{
	//For every enemy
	GameCollectionIterator<EnemyObject> myEnemyIterator = mGameData.getEnemies().getIterator();
	EnemyObject* it;
	while (myEnemyIterator.hasNext())
	{
		it = myEnemyIterator.getNext();

//		randomAI(it, mGameData);	
		toCoreAI(it, mGameData, time);
	}
}


void AISystem::toCoreAI( EnemyObject* it, GameData& mGameData, TimeData time )
{
	AIComponent& currentAIComponent = it->getAIComponent();
	PhysicsComponent& currentPhysicsComponent = it->getPhysicsComponent();
	Core& currentCore = mGameData.getCore();

	if (&currentCore == NULL)
	{
		randomAI(it, mGameData);
		return;
	}

	if( currentAIComponent.getState() == AI_STATE::GET_TO_CORE )
	{
		//if distance from enemy to core is enough
		Ogre::Vector3 enemyPos = it->getPosition();
		Ogre::Vector3 corePos = currentCore.getPosition();

		if( enemyPos.squaredDistance( corePos ) < 400.0*400.0 )
		{
			//change state to shoot at core
			currentAIComponent.setState(AI_STATE::SHOOT_AT_CORE);
			return;
		}

		//get angle between current forward vector and vector to core
		Ogre::Vector3 forwardVector = it->getOrientation() * Ogre::Vector3(0.0, 0.0, 1.0);
			forwardVector.normalise();
		Ogre::Vector3 vectorToCore = corePos - enemyPos;
			vectorToCore.normalise();

		Ogre::Real angleCos = forwardVector.dotProduct( vectorToCore );
		float angleToCore = acos(angleCos);

		//TO DO : jak k¹t jest mniejszy od prêdkoœci k¹towej


		// set orientation to core ( negative z axis to core ... )
		//it->getSceneNode()->lookAt( currentCore.getPosition(), Ogre::Node::TS_WORLD);
		// (... we want positive z axis, so we turn 180 degrees )
		//it->getSceneNode()->yaw( Ogre::Degree(180.0) );



		//get some random values
		float currentVelocity  = float(200 + (rand()%300-100));
		float currentRotVelocity = angleToCore;

		currentPhysicsComponent.setMaxVelocityValue(currentVelocity);

		//set speed of enemy
		it->setTargetVelocity(Ogre::Vector3(0.0, 0.0, 1.0));
		//set it rotation speed
		currentPhysicsComponent.setRotVelocity(currentRotVelocity);
	}
	else if ( currentAIComponent.getState() == AI_STATE::SHOOT_AT_CORE ) {
		//set shoot on the core
		it->setTargetVelocity( Ogre::Vector3( 0.0, 0.0, 0.0 ) );
		currentPhysicsComponent.forceRotVelocity(0.0);
		it->setShoot( time.currentTime );
	}



	
}

void AISystem::randomAI( EnemyObject* it, GameData& mGameData )
{
	PhysicsComponent& currentPhysicsComponent = it->getPhysicsComponent();

	//get some random values
	float currentVelocity  = float(200 + (rand()%300-100));
	float currentRotVelocity = float(0.4 + (rand()%50-25)/10);

	//set speed of enemy
	currentPhysicsComponent.setMaxVelocityValue(currentVelocity);
	//set its vector
	//currentPhysicsComponent.setVelocity(Ogre::Vector3(0.0, 0.0, 1.0));
	it->setTargetVelocity( Ogre::Vector3(0.0, 0.0, 0.5) );
	//set it rotation speed
	currentPhysicsComponent.setRotVelocity(currentRotVelocity);
}


