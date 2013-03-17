#pragma once
#include "InputManager.h"
#include "OgreManager.h"

struct SystemsSet
{
	InputManager  mInputManager;
	OgreManager	  mOgreManager;
	GameData	  mGameData;	
};

struct TimeData
{
	float deltaTime;
	unsigned long currentTime;
};