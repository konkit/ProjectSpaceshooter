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
//		toCoreAI(it, mGameData, time);
		toCoreFlyingAI(it, mGameData, time);
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

void AISystem::toCoreAI( EnemyObject* it, GameData& mGameData, TimeData time )
{
	AIComponent& cntAI = it->getAIComponent();
	PhysicsComponent& cntPhys = it->getPhysicsComponent();
	Core& cntCore = mGameData.getCore();

	if (&cntCore == NULL)
	{
		randomAI(it, mGameData);
		return;
	}

	if( cntAI.getState() == AI_STATE::GET_TO_CORE )
	{
		//change state if needed
		if( it->getPosition().squaredDistance( cntCore.getPosition() ) < 400.0*400.0 )
		{
			//change state to shoot at core
			cntAI.setState(AI_STATE::SHOOT_AT_CORE);
			return;
		}

		//do what is needed
		getToTheCore(it, cntCore);
	}
	else if ( cntAI.getState() == AI_STATE::SHOOT_AT_CORE ) {
		stopAndShootAtCore(it, cntCore, cntPhys, time);
	}
}

void AISystem::toCoreFlyingAI( EnemyObject* it, GameData& mGameData,  TimeData time )	{
	AIComponent& cntAI = it->getAIComponent();
	PhysicsComponent& cntPhys = it->getPhysicsComponent();
	Core& cntCore = mGameData.getCore();

	if (&cntCore == NULL)
	{
		randomAI(it, mGameData);
		return;
	}

	//if in distance1
		//state GET_TO_THE_CORE
		//get to the core
	//if in distance2
		//state SHOOT_AT_CORE
		//shoot at core while moving towards the core
	//if in distance3
		//state TURN_BACK
		//start turning while going full speed
	//if angle to core is more than 90
		//change to state GET_TO_THE_CORE

	if( cntAI.getState() == AI_STATE::GET_TO_CORE )
	{
		std::cout<<"Get to core state \n";

		//change state if needed
		if( it->getPosition().squaredDistance( cntCore.getPosition() ) < 1750.0*1750.0 )
		{
			//change state to shoot at core
			cntAI.setState(AI_STATE::SHOOT_AT_CORE);
			return;
		}

		//do what is needed
		getToTheCore(it, cntCore);
	}	else if ( cntAI.getState() == AI_STATE::SHOOT_AT_CORE ) {
		std::cout<<"shoot at core state \n";

		if( it->getPosition().squaredDistance( cntCore.getPosition() ) < 750.0*750.0 )
		{
			//change state to shoot at core
			cntAI.setState(AI_STATE::TURN_AROUND);
			return;
		}

		flyAndShootAtCore(it, cntCore, cntPhys, time);
	}	else if ( cntAI.getState() == AI_STATE::TURN_AROUND )	{
		std::cout<<"turn around state \n";

		if( it->getPosition().squaredDistance( cntCore.getPosition() ) > 2500.0*2500.0 )
		{
			//change state to shoot at core
			cntAI.setState(AI_STATE::GET_TO_CORE);
			return;
		}

		turnAround(it, cntCore, cntPhys, time);
	}
}



void AISystem::getToTheCore( EnemyObject* it, Core& cntCore)	{

	AIComponent& cntAI = it->getAIComponent();
	PhysicsComponent& cntPhys = it->getPhysicsComponent();
	Ogre::Vector3 enemyPos = it->getPosition();
	Ogre::Vector3 corePos = cntCore.getPosition();

	//get angle between current forward vector and vector to core
	Ogre::Vector3 forwardVector = it->getOrientation() * Ogre::Vector3(0.0, 0.0, 1.0);
		forwardVector.normalise();
	Ogre::Vector3 vectorToCore = corePos - enemyPos;
		vectorToCore.normalise();

	Ogre::Real angleCos = forwardVector.dotProduct( vectorToCore );
	float angleToCore = acos(angleCos);

	//TO DO : jak k¹t jest mniejszy od prêdkoœci k¹towej


	//get some random values
	//float currentVelocity  = float(200 + (rand()%300-100));
	float currentRotVelocity = angleToCore;

	//cntPhys.setMaxVelocityValue(currentVelocity);
	std::cout<<cntPhys.getMaxVelocityValue()<<"\n";

	//set speed of enemy
	it->setTargetVelocity(Ogre::Vector3(0.0, 0.0, 1.0));
	//set it rotation speed
	cntPhys.setRotVelocity(currentRotVelocity);
}



void AISystem::stopAndShootAtCore(EnemyObject* it, Core& cntCore, PhysicsComponent& cntPhys, TimeData time)	{
	Ogre::Vector3 enemyPos = it->getPosition();
	Ogre::Vector3 corePos = cntCore.getPosition();

	//get angle between current forward vector and vector to core
	Ogre::Vector3 forwardVector = it->getOrientation() * Ogre::Vector3(0.0, 0.0, 1.0);
		forwardVector.normalise();
	Ogre::Vector3 vectorToCore = corePos - enemyPos;
		vectorToCore.normalise();

	Ogre::Real angleCos = forwardVector.dotProduct( vectorToCore );
	float angleToCore = acos(angleCos);

	//set shoot on the core
	it->setTargetVelocity( Ogre::Vector3( 0.0, 0.0, 0.0 ) );
	cntPhys.setRotVelocity(angleToCore);
	it->setShoot( time.currentTime );
}


void AISystem::flyAndShootAtCore(EnemyObject* it, Core& cntCore, PhysicsComponent& cntPhys, TimeData time)	{
	Ogre::Vector3 enemyPos = it->getPosition();
	Ogre::Vector3 corePos = cntCore.getPosition();

	//get angle between current forward vector and vector to core
	Ogre::Vector3 forwardVector = it->getOrientation() * Ogre::Vector3(0.0, 0.0, 1.0);
		forwardVector.normalise();
	Ogre::Vector3 vectorToCore = corePos - enemyPos;
		vectorToCore.normalise();

	Ogre::Real angleCos = forwardVector.dotProduct( vectorToCore );
	float angleToCore = acos(angleCos);




	//cntPhys.setMaxVelocityValue(currentVelocity);
	//std::cout<<cntPhys.getMaxVelocityValue()<<"\n";

	//set speed of enemy
	it->setTargetVelocity(Ogre::Vector3(0.0, 0.0, 1.0));
	//set it rotation speed
	cntPhys.setRotVelocity(angleToCore);

	//set shoot on the core
	it->setShoot( time.currentTime );
}


void AISystem::turnAround(EnemyObject* it, Core& cntCore, PhysicsComponent& cntPhys, TimeData time)	{
	Ogre::Vector3 enemyPos = it->getPosition();
	Ogre::Vector3 corePos = cntCore.getPosition();

	//get angle between current forward vector and vector to core
	Ogre::Vector3 forwardVector = it->getOrientation() * Ogre::Vector3(0.0, 0.0, 1.0);
		forwardVector.normalise();
	Ogre::Vector3 vectorToCore = corePos - enemyPos;
		vectorToCore.normalise();

	Ogre::Real angleCos = forwardVector.dotProduct( vectorToCore );
	float angleToCore = acos(angleCos);

	if( abs(angleToCore) >= 3.1415/2.5 )	{
		cntPhys.setRotVelocity(0.0);
	} else {
		cntPhys.setRotVelocity(-0.5);
	}


	//cntPhys.setMaxVelocityValue(currentVelocity);
	//std::cout<<cntPhys.getMaxVelocityValue()<<"\n";

	//set speed of enemy
	it->setTargetVelocity(Ogre::Vector3(0.0, 0.0, 1.0));
}


