#pragma once
#include "InputManager.h"
#include "OgreManager.h"
#include "GameData.h"
#include "PhysicsSystem.h"
#include "ObjectStateUpdateSystem.h"
#include "CollisionSystem.h"
#include "AISystem.h"
#include "GUI_System.h"

/** Struct storing all systems in the game
  *
  * @author Zyga
  */
struct SystemsSet
{
	InputManager  inputManager;
	OgreManager	  ogreManager;
	GameData	  gameData;	
	PhysicsSystem			mPhysicsSystem;
	ObjectStateUpdateSystem mObjectStateSystem;
	CollisionSystem			mCollisionSystem;
	AISystem				mAISystem;
	GUISystem		mGUISystem;

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

