#pragma once
#include "Game.h"
class LevelBuilder : public GameState
{
public:
	LevelBuilder(Game * game);
	~LevelBuilder();

	bool update( SystemsSet & gameSystems, TimeData time );
	void loadLevelDescribe( SystemsSet & gameSystems );

};