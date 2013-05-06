#pragma once
#include "TimeUtility.h"

#include "randomAI.h"
#include "FlyToCore1.h"


/** 
  *
  * 
  * @author 
  */

class AISystem	{
	
public:
	AIStrategy* getAIStrategy( AI_TYPE type );

	void update(GameData& mGameData, TimeData time);

private:

	FlyToCoreAIStrategy1 flyToCore1;
	RandomAIStrategy randomAI;
};