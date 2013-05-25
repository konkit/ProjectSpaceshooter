#pragma once
#include "TimeUtility.h"

#include "randomAI.h"
#include "FlyToCore1.h"


/** System which steers enemies.
  * 
  * @author 
  */

class AISystem	{
	
public:
	/** returns strategy for given AI type */
	AIStrategy* getAIStrategy( AI_TYPE type );

	/** updates GameObject based on current AI state and AI type */
	void update(GameData& mGameData, TimeData time);

private:
	/** strategies for different AI types */
	FlyToCoreAIStrategy1 flyToCore1;
	RandomAIStrategy randomAI;
};