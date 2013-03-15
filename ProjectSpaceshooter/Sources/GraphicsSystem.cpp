#include "GraphicsSystem.h"
#include "Exceptions.h"

void GraphicsSystem::updateNodesAndDrawForPause( GameData& mGameData )
{
	if( !mOgreManager->getRoot()->renderOneFrame() )	
	{
		throw WindowClosedException();
	}
}

void GraphicsSystem::updateBullets( GameData &mGameData )
{
	Ogre::Vector3 tmpPos;
	float tmpAngle;
	GameCollectionIterator<Bullet> * myIterator = mGameData.getBullets().getBulletIterator();
	GameObject* bullet;
	while (myIterator->hasNext())
	{
		bullet = myIterator->getNext();
		tmpPos = bullet->getTransformComponent().getPosition();
		tmpAngle = bullet->getTransformComponent().getAngle();
		bullet->getGraphicsComponent().updateNode(tmpPos, tmpAngle);
	}
	delete myIterator;
}

void GraphicsSystem::updateEnemies( GameData &mGameData )
{
	Ogre::Vector3 tmpPos;
	float tmpAngle;
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
}

void GraphicsSystem::updatePlayer( GameData &mGameData )
{
	Ogre::Vector3 tmpPos;
	float tmpAngle;

	tmpPos = mGameData.getPlayer()->getTransformComponent().getPosition();
	tmpAngle = mGameData.getPlayer()->getTransformComponent().getAngle();
	mGameData.getPlayer()->getGraphicsComponent().updateNode(tmpPos, tmpAngle);
}

void GraphicsSystem::renderFrame()
{
	if( !mOgreManager->getRoot()->renderOneFrame() )	
	{
		throw WindowClosedException();
	}
}

void GraphicsSystem::updateNodesAndDrawForPlay( GameData& mGameData )
{
	updatePlayer(mGameData);
	updateBullets(mGameData);
	updateEnemies(mGameData);
	renderFrame();
}

void GraphicsSystem::init( OgreManager* cntOgreManager )
{
	mOgreManager = cntOgreManager;
}

GraphicsSystem::GraphicsSystem() : mOgreManager(NULL)
{

}
