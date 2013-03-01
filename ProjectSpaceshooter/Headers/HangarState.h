#pragma once
#include "Game.h"
#include "GameStateMain.h"
class HangarState : public GameState
{
public:
	HangarState(Game * game);
	~HangarState();

	virtual bool update();

private:

};