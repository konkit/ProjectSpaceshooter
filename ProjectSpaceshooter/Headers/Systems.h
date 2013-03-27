#pragma once
#include "InputManager.h"
#include "OgreManager.h"
#include "GameData.h"

struct SystemsSet
{
	InputManager  inputManager;
	OgreManager	  ogreManager;
	GameData	  gameData;	
};

struct TimeData
{
	float deltaTime;
	unsigned long currentTime;
};