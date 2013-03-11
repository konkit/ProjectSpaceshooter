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

	void updateNodesAndDrawForPlay( GameData& mGameData )
	{
		//update all nodes
		Ogre::Vector3 tmpPos;
		float tmpAngle;

		tmpPos = mGameData.getPlayer()->getTransformComponent().getPosition();
		tmpAngle = mGameData.getPlayer()->getTransformComponent().getAngle();
		mGameData.getPlayer()->getGraphicsComponent().updateNode(tmpPos, tmpAngle);

		GameObjectsCollectionIterator<GameObject> * myIterator = mGameData.getBullets().getIterator();
		while (myIterator->hasNext())
		{
			tmpPos = myIterator->getNext()->getTransformComponent().getPosition();
			tmpAngle = myIterator->getNext()->getTransformComponent().getAngle();
			myIterator->getNext()->getGraphicsComponent().updateNode(tmpPos, tmpAngle);
		}
		delete myIterator;


		// Render a frame
		if( !mOgreManager->getRoot()->renderOneFrame() )	
		{
			throw WindowClosedException();
		}
	}

	void updateNodesAndDrawForPause( GameData& mGameData )
	{
		if( !mOgreManager->getRoot()->renderOneFrame() )	
		{
			throw WindowClosedException();
		}
	}

private:
	OgreManager* mOgreManager;
};