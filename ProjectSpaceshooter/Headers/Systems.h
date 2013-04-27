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
#ifdef _DEBUG
	DebugDrawer  *          cntDebugDrawer;
#endif // _DEBUG
	~SystemsSet()
	{
#ifdef _DEBUG
		if (cntDebugDrawer != NULL)
		{
			cntDebugDrawer->clear();
			delete cntDebugDrawer;
		}
#endif // _DEBUG
	}
};

