#pragma once
#include "Game.h"
class GameState
{
protected:
	Game * game;
public:
	GameState(Game * game): game(game){};
	virtual bool update() = 0;
	virtual ~GameState(void);
};



