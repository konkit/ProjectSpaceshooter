#pragma once
#include "Game.h"
#include "GameStateMain.h"
class PauseState : public GameState
{
public:
	PauseState(Game * game);
	~PauseState();
	virtual bool update();

private:
};