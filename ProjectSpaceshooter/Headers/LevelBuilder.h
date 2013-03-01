#pragma once
#include "Game.h"
#include "GameStateMain.h"
class LevelBuilder : public GameState
{
public:
	LevelBuilder(Game * game);
	~LevelBuilder();
	virtual bool update();
};