#pragma once

#include "GameObject.h"

/**
  * Abstract class for strategy pattern for Artificial Intelligence
  * Subclasses of this class implements update method which governs the behaviour 
  * of the enemy */
class AIStrategy	{

public:
	/**
	  * Updates position and behaviour of enemy
	  */
	virtual void update( EnemyObject* it, GameData& mGameData, TimeData time  ) = 0;
};
