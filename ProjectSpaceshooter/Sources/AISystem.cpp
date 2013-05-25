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

		// select AI behaviour 
		AIStrategy* currentStrategy = getAIStrategy( it->getAIComponent().getType() );

		//update the AI with given strategy
		try {
			currentStrategy->update(it, mGameData, time);
		} catch (CoreNullException e)	{
			//The Core is probably destroyed, run random AI mode
			randomAI.update(it, mGameData, time);
		} catch (EnemyNullException e)	{
			//Enemy pointer is null, do nothing
			continue;
		}


	}
}

AIStrategy* AISystem::getAIStrategy( AI_TYPE type )	{
	//temporary, to be changed
	
	if( type == AI_TYPE::fighter )	{
		return &flyToCore1;
	} else if( type == AI_TYPE::defender )	{
		return &flyToCore1;
	} else {
		throw My_Exception("Unknown ai type ");
	}
}

