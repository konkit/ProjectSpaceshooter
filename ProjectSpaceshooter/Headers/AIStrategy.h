#pragma once

#include "GameObject.h"

class AIStrategy	{

public:
	virtual void update( EnemyObject* it, GameData& mGameData, TimeData time  ) = 0;
};
