#pragma once
#include "Game.h"
class HangarState : public GameState
{
public:
	HangarState(Game * game);
	~HangarState(){};

	virtual bool update(){return true;};

private:

};