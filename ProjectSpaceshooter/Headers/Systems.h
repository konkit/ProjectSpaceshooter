#pragma once
#include "InputManager.h"
#include "OgreManager.h"
#include "GameData.h"
#include "PhysicsSystem.h"
#include "ObjectStateUpdateSystem.h"
#include "CollisionSystem.h"
#include "AISystem.h"

struct SystemsSet
{
	InputManager  inputManager;
	OgreManager	  ogreManager;
	GameData	  gameData;	
	PhysicsSystem			mPhysicsSystem;
	ObjectStateUpdateSystem mObjectStateSystem;
	CollisionSystem			mCollisionSystem;
	AISystem				mAISystem;
};

