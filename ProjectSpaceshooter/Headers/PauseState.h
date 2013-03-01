#pragma once
#include "Game.h"
class PauseState : public GameState
{
public:
	PauseState(Game * game);
	~PauseState(){};
	virtual bool update(){return true;};

private:
};