#pragma once
#include "Game.h"
class PauseState : public GameState
{
public:
	PauseState(Game * game);
	~PauseState(){};
	void createCamera();
	virtual bool update();

private:
};