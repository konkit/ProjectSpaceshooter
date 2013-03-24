#pragma once
#include "InputManager.h"
#include "OgreManager.h"

struct SystemsSet
{
	InputManager  mInputManager;
	OgreManager	  mOgreManager;
	GameData	  mGameData;	

	void update( SystemsSet mGameSystems, TimeData time ) 
	{
		throw std::exception("The method or operation is not implemented.");
	}


};

struct TimeData
{
	float deltaTime;
	unsigned long currentTime;
};