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

		GameObjectsCollectionIterator<Bullet> * myIterator = mGameData.getBullets().getCollection().getIterator();
		GameObject* it;
		while (myIterator->hasNext())
		{
			it = myIterator->getNext();
			tmpPos = it->getTransformComponent().getPosition();
			tmpAngle = it->getTransformComponent().getAngle();
			it->getGraphicsComponent().updateNode(tmpPos, tmpAngle);
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