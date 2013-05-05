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
		toCoreAI2(it, mGameData, time);
//		toCoreFlyingAI(it, mGameData, time);
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
		if( it->getPosition().squaredDistance( cntCore.getPosition() ) < 1000.0*1000.0 )
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

void AISystem::toCoreAI2( EnemyObject* it, GameData& mGameData, TimeData time )
{
	AIComponent& cntAI = it->getAIComponent();
	PhysicsComponent& cntPhys = it->getPhysicsComponent();
	Core& cntCore = mGameData.getCore();

	if (&cntCore == NULL)
	{
		randomAI(it, mGameData);
		return;
	}


	if( cntAI.getState() == AI_STATE::GET_TO_CORE )	{
		//change state if needed
		if( it->getPosition().squaredDistance( cntCore.getPosition() ) < 2000.0*2000.0 )
		{
			//change state to shoot at core
			cntAI.setState(AI_STATE::SHOOT_AT_CORE);
			return;
		}

		//move towards core
		Ogre::Vector3 vectorToTarget = cntCore.getPosition() - it->getPosition();
			vectorToTarget.normalise();

		it->getPhysicsComponent().setTargetVelocity(Ogre::Quaternion(), vectorToTarget);	

		
		
	} else if ( cntAI.getState() == AI_STATE::SHOOT_AT_CORE ) {
		//change state if needed
		if( it->getPosition().squaredDistance( cntCore.getPosition() ) < 1000.0*1000.0 )
		{
			//change state to shoot at core
			cntAI.setState(AI_STATE::TURN_AROUND);

			Ogre::Vector3 vectorToTarget = cntCore.getPosition() - it->getPosition();
				vectorToTarget.normalise();

			Ogre::Vector3 perpendicularVector = vectorToTarget.crossProduct( Ogre::Vector3::UNIT_Y );

			cntAI.cntTarget = cntCore.getPosition() + perpendicularVector * 2500.0;

			return;
		}

		//move towards core
		Ogre::Vector3 vectorToTarget = cntCore.getPosition() - it->getPosition();
			vectorToTarget.normalise();

		it->getPhysicsComponent().setTargetVelocity(Ogre::Quaternion(), vectorToTarget);

		Ogre::Quaternion newOrient = Ogre::Vector3::UNIT_Z.getRotationTo(vectorToTarget);
		it->setOrientation( newOrient );

		it->setShoot(time.currentTime);
	} else if( cntAI.getState() == AI_STATE::TURN_AROUND )	{
		//change state if needed
		if( it->getPosition().squaredDistance( cntCore.getPosition() ) > 2000.0*2000.0 )
		{
			//change state to shoot at core
			cntAI.setState(AI_STATE::GET_TO_CORE);
			return;
		}

		//move away the core
		Ogre::Vector3 vectorToTarget = cntAI.cntTarget - it->getPosition();
			vectorToTarget.normalise();

		it->getPhysicsComponent().setTargetVelocity(Ogre::Quaternion(), vectorToTarget);
	}

}





void AISystem::getToTheCore( EnemyObject* it, Core& cntCore)	{
	//count angle to core
	float angleToCore = getAngleToTarget(it, &cntCore);
	float rotVelocityValue = it->getPhysicsComponent().getRotVelocityValue();
	
	if( abs(angleToCore) > abs( rotVelocityValue ) )	{
		if( angleToCore * rotVelocityValue < 0.0 )	{
			it->getPhysicsComponent().forceRotVelocity(-rotVelocityValue);
		} else {
			it->getPhysicsComponent().forceRotVelocity(rotVelocityValue);
		}
	} else {
		it->getPhysicsComponent().forceRotVelocity(angleToCore);
	}
	
	it->setTargetVelocity(Ogre::Vector3(0.0, 0.0, 1.0));
}



void AISystem::stopAndShootAtCore(EnemyObject* it, Core& cntCore, PhysicsComponent& cntPhys, TimeData time)	{
	//count angle to core
	float angleToCore = getAngleToTarget(it, &cntCore);
	float rotVelocityValue = it->getPhysicsComponent().getRotVelocityValue();

	if( abs(angleToCore) > abs( rotVelocityValue ) )	{
		if( angleToCore * rotVelocityValue < 0.0 )	{
			it->getPhysicsComponent().forceRotVelocity(-rotVelocityValue);
		} else {
			it->getPhysicsComponent().forceRotVelocity(rotVelocityValue);
		}
	} else {
		it->getPhysicsComponent().forceRotVelocity(angleToCore);
	}
	
	it->setTargetVelocity(Ogre::Vector3(0.0, 0.0, 0.0));
	//SHOOT !
	it->setShoot( time.currentTime );
}


float AISystem::getAngleToTarget(EnemyObject* it, GameObject* target )	{
	Ogre::Vector3 enemyPos = it->getPosition();
	Ogre::Vector3 targetPos = target->getPosition();

	//get angle between current forward vector and vector to core
	Ogre::Vector3 forwardVector = it->getOrientation() * Ogre::Vector3(0.0, 0.0, 1.0);
		forwardVector.normalise();
	Ogre::Vector3 vectorToCore = targetPos - enemyPos;
		vectorToCore.normalise();

	Ogre::Real angleCos = forwardVector.dotProduct( vectorToCore );

	if( angleCos < -1.0)
		angleCos = -0.9999999;
	else if( angleCos > 1.0)	
		angleCos = 0.99999999;

	float angleToCore = acos(angleCos);

	return angleToCore;
}
