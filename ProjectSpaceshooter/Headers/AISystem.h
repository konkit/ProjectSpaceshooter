#pragma once
#include "TimeUtility.h"

#include "randomAI.h"
#include "FlyToCore1.h"


/** System which steers enemies.
  * 
  * @author konkit
  */

class AISystem	{
	
public:
	/** returns strategy for given AI type 
	  * @param type - type of AI
	  */
	AIStrategy* getAIStrategy( AI_TYPE type );

	/** updates GameObject based on current AI state and AI type 
	  * @param mGameData - GameData object
	  * @param time - Time object (has info abount time since start and fraction of time since last frame
	  */
	void update(GameData& mGameData, TimeData time);

private:
	/** strategies for different AI types */
	FlyToCoreAIStrategy1 flyToCore1;
	RandomAIStrategy randomAI;
};