#pragma once

#include "OgreManager.h"
#include "GameData.h"

class GraphicsSystem
{
public:
	GraphicsSystem() : mOgreManager(NULL)	{
	}


	void init(OgreManager* cntOgreManager)
	{
		mOgreManager = cntOgreManager;
	}

	void updateNodesAndDraw( GameData& mGameData )
	{
		//update all nodes
		float tmpX, tmpY, tmpZ, tmpAngle;

		tmpX = mGameData.getPlayer()->getTransformComponent().getX();
		tmpY = mGameData.getPlayer()->getTransformComponent().getY();
		tmpZ = mGameData.getPlayer()->getTransformComponent().getZ();
		tmpAngle = mGameData.getPlayer()->getTransformComponent().getAngle();

		mGameData.getPlayer()->getGraphicsComponent().updateNode(tmpX, tmpY, tmpZ, tmpAngle);

		// Render a frame
		mOgreManager->getRoot()->renderOneFrame();
	}

private:
	OgreManager* mOgreManager;
};