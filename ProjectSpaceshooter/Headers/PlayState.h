#pragma once
#include "Game.h"
class PlayState : public GameState
{
private:
public:
	PlayState(Game * game);
	~PlayState(){};

	virtual bool update();;

private:
};
