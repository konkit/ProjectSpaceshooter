#pragma once

#include "AIStrategy.h"
#include "Exceptions.h"

/**
  * AI mode where enemy is in constant motion, shooting at core and turning around 
  * @author konkit
  */
class FlyToCoreAIStrategy1 : public AIStrategy	{

public:
	virtual void update( EnemyObject* it, GameData& mGameData, TimeData time )
	{
		//Check if EnemyObject even exists
		if( it == NULL )	{
			throw EnemyNullException();
		}

		AIComponent& cntAI = it->getAIComponent();
		PhysicsComponent& cntPhys = it->getPhysicsComponent();
		Core& cntCore = mGameData.getCore();

		//Check if Core even exists
		if( &cntCore == NULL )	{
			throw CoreNullException();
		}

		if( cntAI.getState() == AI_STATE::GET_TO_CORE )	{
			getToCore(it, mGameData, time);		
		} else if ( cntAI.getState() == AI_STATE::SHOOT_AT_CORE ) {
			shootAtCore(it, mGameData, time);
		} else if( cntAI.getState() == AI_STATE::TURN_AWAY )	{
			turnAway(it, mGameData, time);
		} else if( cntAI.getState() == AI_STATE::TURN_AROUND )	{
			turnOver(it, mGameData, time);
		}
	}

private:
	void getToCore(EnemyObject* it, GameData& mGameData, TimeData time){
		AIComponent& cntAI = it->getAIComponent();
		PhysicsComponent& cntPhys = it->getPhysicsComponent();
		Core& cntCore = mGameData.getCore();
		
		if( it->getPosition().squaredDistance( cntCore.getPosition() ) < 2000.0*2000.0 )
		{
			//change state to shoot at core
			cntAI.setState(AI_STATE::SHOOT_AT_CORE);
			return;
		}

		//move towards core
		Ogre::Vector3 vectorToTarget = cntCore.getPosition() - it->getPosition();
			vectorToTarget.normalise();

		it->getPhysicsComponent().setTargetVelocityValue( 1.0 );	

		Ogre::Vector3 cntVelocity = it->getPhysicsComponent().getCurrentVelocity();

		Ogre::Quaternion newOrient = Ogre::Vector3::UNIT_Z.getRotationTo(vectorToTarget);
		it->setOrientation( newOrient );
	}

	void shootAtCore(EnemyObject* it, GameData& mGameData, TimeData time)	{
		AIComponent& cntAI = it->getAIComponent();
		PhysicsComponent& cntPhys = it->getPhysicsComponent();
		Core& cntCore = mGameData.getCore();

		//change state if needed
		if( it->getPosition().squaredDistance( cntCore.getPosition() ) < 1000.0*1000.0 )
		{
			//change state to shoot at core
			cntAI.setState(AI_STATE::TURN_AWAY);

			Ogre::Vector3 vectorToTarget = cntCore.getPosition() - it->getPosition();
				vectorToTarget.normalise();

			Ogre::Vector3 perpendicularVector = vectorToTarget.crossProduct( Ogre::Vector3::UNIT_Y );

			cntAI.setCurrentTargetPos( cntCore.getPosition() + perpendicularVector * 2500.0 );

			return;
		}

		//move towards core
		Ogre::Vector3 vectorToTarget = cntCore.getPosition() - it->getPosition();
			vectorToTarget.normalise();

		it->getPhysicsComponent().setTargetVelocityValue( 1.0 );

		Ogre::Quaternion newOrient = Ogre::Vector3::UNIT_Z.getRotationTo(vectorToTarget);
		it->setOrientation( newOrient );

		it->setShoot(time.currentTime);
	}

	void turnAway(EnemyObject* it, GameData& mGameData, TimeData time)	{
		AIComponent& cntAI = it->getAIComponent();
		PhysicsComponent& cntPhys = it->getPhysicsComponent();
		Core& cntCore = mGameData.getCore();

		//change state if needed
		if( it->getPosition().squaredDistance( cntAI.getCurrentTargetPos() ) < 100.0*100.0 )
		{
			//change state to shoot at core
			cntAI.setState(AI_STATE::TURN_AROUND);
			
			Ogre::Vector3 vectorToTarget = cntCore.getPosition() - it->getPosition();
				vectorToTarget.normalise();

			Ogre::Vector3 perpendicularVector =  vectorToTarget.crossProduct( Ogre::Vector3::UNIT_Y );

			cntAI.setCurrentTargetPos( cntAI.getCurrentTargetPos() + perpendicularVector * 2500.0 );

			return;
		}

		//move away the core
		Ogre::Vector3 vectorToTarget = cntAI.getCurrentTargetPos() - it->getPosition();
			vectorToTarget.normalise();

		it->getPhysicsComponent().setTargetVelocityValue(1.0);

		Ogre::Vector3 cntVelocity = it->getPhysicsComponent().getCurrentVelocity();

		Ogre::Quaternion newOrient = Ogre::Vector3::UNIT_Z.getRotationTo(vectorToTarget);
		it->setOrientation( newOrient );
	}

	void turnOver(EnemyObject* it, GameData& mGameData, TimeData time)	{
		AIComponent& cntAI = it->getAIComponent();
		PhysicsComponent& cntPhys = it->getPhysicsComponent();
		Core& cntCore = mGameData.getCore();

		//change state if needed
		if( it->getPosition().squaredDistance( cntAI.getCurrentTargetPos() ) < 100.0*100.0 )
		{
			//change state to shoot at core
			cntAI.setState(AI_STATE::GET_TO_CORE);
			return;
		}

		//move away the core
		Ogre::Vector3 vectorToTarget = cntAI.getCurrentTargetPos() - it->getPosition();
			vectorToTarget.normalise();

		it->getPhysicsComponent().setTargetVelocityValue(1.0);

		Ogre::Vector3 cntVelocity = it->getPhysicsComponent().getCurrentVelocity();

		Ogre::Quaternion newOrient = Ogre::Vector3::UNIT_Z.getRotationTo(vectorToTarget);
		it->setOrientation( newOrient );
	}

	virtual void flyRandomly( EnemyObject* it, GameData& mGameData, TimeData time  )
	{
		PhysicsComponent& currentPhysicsComponent = it->getPhysicsComponent();

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
