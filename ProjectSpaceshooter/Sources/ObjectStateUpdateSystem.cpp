#include "ObjectStateUpdateSystem.h"

void ObjectStateUpdateSystem::update( GameData& mGameData, TimeData& time )
{
	//for every gameobject
	//if one needs to be removed - remove it
	//if one needs to be created - create it

	//creating bullets when player is shooting
	if( mGameData.getPlayer()->isShooting() == true)	{
		//get player's data required to create new bullet
		GameObject* player = mGameData.getPlayer();
		Ogre::Quaternion playerOrientation = player->getOrientation();
		Ogre::Vector3 playerPos = player->getPosition();

		//create new bullet
		mGameData.getBullets().instantiate(0, mGameData.getSceneManagerFor(GAME_STATES::PLAY), playerPos, playerOrientation);

		//set shooting as false
		mGameData.getPlayer()->unsetShoot();
	}

	//spawning enemies
	mGameData.getLevelDescription().spawn(mGameData, time.currentTime);

	//deleting bullets when time to Live is up.
	GameCollectionIterator<Bullet> * bulletIterator = mGameData.getBullets().getBulletIterator();
	GameObject* it;
	while (bulletIterator->hasNext())
	{
		it = bulletIterator->getNext();

		it->getGamelogicComponent().decreaseTimeToLive();

		if( it->getGamelogicComponent().isStillAlive() == false )	{

			//remove from collection
			Bullet* removedObject = dynamic_cast<Bullet*> (it);
			it->getSceneNode()->detachAllObjects();	//PROWIZORKA!!!
			mGameData.getSceneManagerFor(GAME_STATES::PLAY)->getRootSceneNode()->removeAndDestroyChild( it->getSceneNode()->getName() );
			mGameData.getBullets().getCollection().deleteObject(removedObject);

			//create explosion

		}

	}
	delete bulletIterator;

	//deleting enemies when dead.
	GameCollectionIterator<EnemyObject> * enemyIterator = mGameData.getEnemys().getEnemyIterator();
	while (enemyIterator->hasNext())
	{
		it = enemyIterator->getNext();
		if( it->getGamelogicComponent().isStillAlive() == false )	{
			//remove from collection
			EnemyObject* removedObject = dynamic_cast<EnemyObject*> (it);
			it->getSceneNode()->detachAllObjects();	//PROWIZORKA!!!
			mGameData.getSceneManagerFor(GAME_STATES::PLAY)->getRootSceneNode()->removeAndDestroyChild( it->getSceneNode()->getName() );
			mGameData.getEnemys().getCollection().deleteObject(removedObject);
		}

	}
	delete enemyIterator;
}

