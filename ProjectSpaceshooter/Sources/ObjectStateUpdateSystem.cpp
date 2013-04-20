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
		float bulletPower = mGameData.getPlayer()->getCurrentWeapon().getPower();

		Bullet* newBullet = mGameData.getBullets().instantiate(1, mGameData.getSceneManagerFor(GAME_STATES::PLAY));
			//set player pos
			newBullet->setPosition(playerPos);
			//set player orientation
			newBullet->setOrientation(playerOrientation);
			//set owner
			newBullet->setOwner(player);
			//set time to live
			newBullet->getTTLComponent().setTimeToLive(3.0);
			//set speed
			newBullet->setTargetVelocity( Ogre::Vector3(0.0, 0.0, 1.0) );
			newBullet->setCurrentSpeedToMax();

		//set shooting as false
		mGameData.getPlayer()->unsetShoot();
	}

	//spawning enemies
	mGameData.getLevelDescription().spawn(mGameData, time.currentTime);

	//deleting bullets when time to Live is up.
	GameCollectionIterator<Bullet> bulletIterator = mGameData.getBullets().getIterator();
	Bullet* bulletIt;
	while (bulletIterator.hasNext())
	{
		bulletIt = bulletIterator.getNext();

		bulletIt->getTTLComponent().decreaseTimeToLive(time.deltaTime);

		if( bulletIt->isDead() == true )	{
			//remove from collection
			Bullet* removedObject = dynamic_cast<Bullet*> (bulletIt);
			bulletIt->getSceneNode()->detachAllObjects();	
			mGameData.getSceneManagerFor(GAME_STATES::PLAY)->getRootSceneNode()->removeAndDestroyChild( bulletIt->getSceneNode()->getName() );
			mGameData.getBullets().getCollection().deleteObject(removedObject);
		}

	}

	//parsing through enemies
	GameCollectionIterator<EnemyObject> enemyIterator = mGameData.getEnemies().getIterator();
	EnemyObject* enemyIt;
	while (enemyIterator.hasNext())
	{
		enemyIt = enemyIterator.getNext();

		//removing when dead
		if( enemyIt->isDead() == true )	{
			//create explosion
			EffectObject* newExplosion = mGameData.getEffects().instantiate(1, mGameData.getSceneManagerFor(GAME_STATES::PLAY));
			newExplosion->setPosition( enemyIt->getPosition()  );

			//remove from collection
			EnemyObject* removedObject = dynamic_cast<EnemyObject*> (enemyIt);
			enemyIt->getSceneNode()->detachAllObjects();
			mGameData.getSceneManagerFor(GAME_STATES::PLAY)->getRootSceneNode()->removeAndDestroyChild( enemyIt->getSceneNode()->getName() );
			mGameData.getEnemies().getCollection().deleteObject(removedObject);
		}

		//creating bullets when enemy is shooting
		if( enemyIt->isShooting() == true)	{
			//get data required to create new bullet
			Ogre::Quaternion enemyOrientation = enemyIt->getOrientation();
			Ogre::Vector3 enemyPos = enemyIt->getPosition();
			float bulletPower = enemyIt->getCurrentWeapon().getPower();

			Bullet* newBullet = mGameData.getBullets().instantiate(1, mGameData.getSceneManagerFor(GAME_STATES::PLAY));
				//set player pos
				newBullet->setPosition(enemyPos);
				//set player orientation
				newBullet->setOrientation(enemyOrientation);
				//set owner
				newBullet->setOwner(enemyIt);
				//set time to live
				newBullet->getTTLComponent().setTimeToLive(3.0);
				//set speed
				newBullet->setTargetVelocity( Ogre::Vector3(0.0, 0.0, 1.0) );
				newBullet->setCurrentSpeedToMax();

			//set shooting as false
			enemyIt->unsetShoot();
		}

	}

	GameCollectionIterator<EffectObject> effectIterator = mGameData.getEffects().getIterator();
	EffectObject* effectIt;
	while (effectIterator.hasNext())
	{
		effectIt = effectIterator.getNext();

		effectIt->getTTLComponent().decreaseTimeToLive(time.deltaTime);

		if( effectIt->isDead() == true )	{
			//remove from collection
			EffectObject* removedObject = dynamic_cast<EffectObject*> (effectIt);
			effectIt->getSceneNode()->detachAllObjects();	
			mGameData.getSceneManagerFor(GAME_STATES::PLAY)->getRootSceneNode()->removeAndDestroyChild( effectIt->getSceneNode()->getName() );
			mGameData.getEffects().getCollection().deleteObject(removedObject);
		}
	}
}

