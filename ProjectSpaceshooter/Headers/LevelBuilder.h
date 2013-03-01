#pragma once
#include "Game.h"
class LevelBuilder : public GameState
{
public:
	LevelBuilder(Game * game);
	~LevelBuilder();
	virtual bool update();
};