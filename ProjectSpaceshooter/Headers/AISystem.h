#pragma once
#include "TimeUtility.h"


/** 
  *
  * 
  * @author 
  */
class AISystem	{
	
public:
	void update(GameData& mGameData, TimeData time);

	void randomAI(EnemyObject* it, GameData& mGameData);

	void toCoreAI( EnemyObject* it, GameData& mGameData,  TimeData time);
		void getToTheCore( EnemyObject* it, Core& cntCore );
		void stopAndShootAtCore( EnemyObject* it, Core& cntCore, PhysicsComponent& cntPhys, TimeData time );
		

	void toCoreFlyingAI( EnemyObject* it, GameData& mGameData,  TimeData time );
		void turnAround( EnemyObject* it, Core& cntCore, PhysicsComponent& cntPhys, TimeData time );
		void flyAndShootAtCore( EnemyObject* it, Core& cntCore, PhysicsComponent& cntPhys, TimeData time );

	float getAngleToTarget(EnemyObject* it, GameObject* target );

private:


};