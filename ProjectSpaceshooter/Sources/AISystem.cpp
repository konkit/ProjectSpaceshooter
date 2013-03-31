#include "AISystem.h"


void AISystem::toCoreAI( EnemyObject* it, GameData& mGameData )
{
	PhysicsComponent& currentPhysicsComponent = it->getPhysicsComponent();
	Core& currentCore = mGameData.getCore();

	// set orientation to core ( negative z axis to core ... )
	it->getSceneNode()->lookAt( currentCore.getPosition(), Ogre::Node::TS_WORLD);
	// (... we want positive z axis, so we turn 180 degrees )
	it->getSceneNode()->yaw( Ogre::Degree(180.0) );

	//get some random values
	float currentVelocity  = 200 + (rand()%300-100);
	float currentRotVelocity = 0.0;

	//set speed of enemy
	currentPhysicsComponent.setVelocityValue(currentVelocity);
	//set its vector
	currentPhysicsComponent.setVelocity(Ogre::Vector3(0.0, 0.0, 1.0));
	//set it rotation speed
	currentPhysicsComponent.setRotVelocity(currentRotVelocity);
}

void AISystem::randomAI( EnemyObject* it, GameData& mGameData )
{
	PhysicsComponent& currentPhysicsComponent = it->getPhysicsComponent();

	//get some random values
	float currentVelocity  = 200 + (rand()%300-100);
	float currentRotVelocity = 0.4 + (rand()%50-25)/10;

	//set speed of enemy
	//currentPhysicsComponent.setVelocityValue(currentVelocity);
	//set its vector
	//currentPhysicsComponent.setVelocity(Ogre::Vector3(0.0, 0.0, 1.0));
	it->setTargetVelocity( Ogre::Vector3(0.0, 0.0, 1.0) );
	//set it rotation speed
	currentPhysicsComponent.setRotVelocity(currentRotVelocity);
}

void AISystem::update( GameData& mGameData, float deltaTime )
{
	//For every enemy
	GameCollectionIterator<EnemyObject> * myEnemyIterator = mGameData.getEnemies().getIterator();
	EnemyObject* it;
	while (myEnemyIterator->hasNext())
	{
		it = myEnemyIterator->getNext();

		randomAI(it, mGameData);	
//		toCoreAI(it, mGameData);
	}
	delete myEnemyIterator;
}

