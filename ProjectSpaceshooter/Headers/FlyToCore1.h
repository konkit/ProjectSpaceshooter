#pragma once

#include "AIStrategy.h"

class FlyToCoreAIStrategy1 : public AIStrategy	{

public:
	virtual void update( EnemyObject* it, GameData& mGameData, TimeData time )
	{
		AIComponent& cntAI = it->getAIComponent();
		PhysicsComponent& cntPhys = it->getPhysicsComponent();
		Core& cntCore = mGameData.getCore();

		/*
		if (&cntCore == NULL)
		{
			randomAI(it, mGameData);
			return;
		}
		*/

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

			Ogre::Vector3 cntVelocity = it->getPhysicsComponent().getCurrentVelocity();

			Ogre::Quaternion newOrient = Ogre::Vector3::UNIT_Z.getRotationTo(cntVelocity);
			it->setOrientation( newOrient );
		
		} else if ( cntAI.getState() == AI_STATE::SHOOT_AT_CORE ) {
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
		} else if( cntAI.getState() == AI_STATE::TURN_AWAY )	{
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
	
		else if( cntAI.getState() == AI_STATE::TURN_AROUND )	{
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
	}

};
