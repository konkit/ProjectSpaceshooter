#pragma once

#include "AIStrategy.h"

class FlyToCoreAIStrategy1 : public AIStrategy	{

public:
	virtual void update( EnemyObject* it, GameData& mGameData, TimeData time )
	{
		AIComponent& cntAI = it->getAIComponent();
		PhysicsComponent& cntPhys = it->getPhysicsComponent();
		Core& cntCore = mGameData.getCore();		

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

		it->getPhysicsComponent().setTargetVelocity(Ogre::Quaternion(), vectorToTarget);	

		Ogre::Vector3 cntVelocity = it->getPhysicsComponent().getCurrentVelocity();

		Ogre::Quaternion newOrient = Ogre::Vector3::UNIT_Z.getRotationTo(cntVelocity);
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
	}

	void turnAway(EnemyObject* it, GameData& mGameData, TimeData time)	{
		AIComponent& cntAI = it->getAIComponent();
		PhysicsComponent& cntPhys = it->getPhysicsComponent();
		Core& cntCore = mGameData.getCore();

		//change state if needed
		if( it->getPosition().squaredDistance( cntAI.cntTarget ) < 100.0*100.0 )
		{
			//change state to shoot at core
			cntAI.setState(AI_STATE::TURN_AROUND);
			
			Ogre::Vector3 vectorToTarget = cntCore.getPosition() - it->getPosition();
				vectorToTarget.normalise();

			Ogre::Vector3 perpendicularVector =  vectorToTarget.crossProduct( Ogre::Vector3::UNIT_Y );

			cntAI.cntTarget = cntAI.cntTarget + perpendicularVector * 2500.0;

			return;
		}

		//move away the core
		Ogre::Vector3 vectorToTarget = cntAI.cntTarget - it->getPosition();
			vectorToTarget.normalise();

		it->getPhysicsComponent().setTargetVelocity(Ogre::Quaternion(), vectorToTarget);

		Ogre::Vector3 cntVelocity = it->getPhysicsComponent().getCurrentVelocity();

		Ogre::Quaternion newOrient = Ogre::Vector3::UNIT_Z.getRotationTo(cntVelocity);
		it->setOrientation( newOrient );
	}

	void turnOver(EnemyObject* it, GameData& mGameData, TimeData time)	{
		AIComponent& cntAI = it->getAIComponent();
		PhysicsComponent& cntPhys = it->getPhysicsComponent();
		Core& cntCore = mGameData.getCore();

		//change state if needed
		if( it->getPosition().squaredDistance( cntAI.cntTarget ) < 100.0*100.0 )
		{
			//change state to shoot at core
			cntAI.setState(AI_STATE::GET_TO_CORE);
			return;
		}

		//move away the core
		Ogre::Vector3 vectorToTarget = cntAI.cntTarget - it->getPosition();
			vectorToTarget.normalise();

		it->getPhysicsComponent().setTargetVelocity(Ogre::Quaternion(), vectorToTarget);

		Ogre::Vector3 cntVelocity = it->getPhysicsComponent().getCurrentVelocity();

		Ogre::Quaternion newOrient = Ogre::Vector3::UNIT_Z.getRotationTo(cntVelocity);
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
		it->setTargetVelocity( Ogre::Vector3(0.0, 0.0, 0.5) );
		//set it rotation speed
		currentPhysicsComponent.setRotVelocity(currentRotVelocity);
	}





};