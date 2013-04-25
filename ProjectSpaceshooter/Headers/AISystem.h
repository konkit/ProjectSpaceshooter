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


private:


};