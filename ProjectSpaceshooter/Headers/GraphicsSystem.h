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

		//Z³amane prawo Diameter - do poprawy
		GameCollectionIterator<Bullet> * myIterator = mGameData.getBullets().getCollection().getIterator();
		GameObject* bullet;
		while (myIterator->hasNext())
		{
			bullet = myIterator->getNext();
			tmpPos = bullet->getTransformComponent().getPosition();
			tmpAngle = bullet->getTransformComponent().getAngle();
			bullet->getGraphicsComponent().updateNode(tmpPos, tmpAngle);
		}
		delete myIterator;

		GameCollectionIterator<EnemyObject> * enemyIterator = mGameData.getEnemys().getEnemyIterator();
		EnemyObject * enemy;
		while (enemyIterator->hasNext())
		{
			enemy = enemyIterator->getNext();
			tmpPos = enemy->getTransformComponent().getPosition();
			tmpAngle = enemy->getTransformComponent().getAngle();
			enemy->getGraphicsComponent().updateNode(tmpPos, tmpAngle);
		}
		delete enemyIterator;

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