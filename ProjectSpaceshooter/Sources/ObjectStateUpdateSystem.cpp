#include "ObjectStateUpdateSystem.h"

void ObjectStateUpdateSystem::update( GameData& mGameData, TimeData& time )
{
	//for every gameobject
	//if one needs to be removed - remove it
	//if one needs to be created - create it

	//creating bullets when player is shooting

	removeDeadObjects(mGameData);

	if( mGameData.getPlayer()->isShooting() == true)	
	{
		//get player's data required to create new bullet
		Ship* player = mGameData.getPlayer();
		Ogre::Quaternion playerOrientation = player->getOrientation();
		Ogre::Vector3 playerPos = player->getPosition();

		Bullet* newBullet = mGameData.instantiateBullet(player->getBulletIDFromActiveWeapon());
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

	}

	//parsing through enemies
	GameCollectionIterator<EnemyObject> enemyIterator = mGameData.getEnemies().getIterator();
	EnemyObject* enemyIt;
	while (enemyIterator.hasNext())
	{
		enemyIt = enemyIterator.getNext();

		//creating bullets when enemy is shooting
		if( enemyIt->isShooting() == true)	{
			//get data required to create new bullet
			Ogre::Quaternion enemyOrientation = enemyIt->getOrientation();
			Ogre::Vector3 enemyPos = enemyIt->getPosition();

			Bullet* newBullet = mGameData.instantiateBullet(enemyIt->getBulletIDFromActiveWeapon());
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
	}
}

void ObjectStateUpdateSystem::removeDeadObjects( GameData& mGameData)
{
	auto iterator = mGameData.getColidingObjectsIterator();
	GameObject_WithCollider * removedObject;
	iterator.skipPlayer();
	while (iterator.hasNext())
	{
		removedObject = iterator.getNext();
		if (removedObject->isDead())
		{
			createExplosionFor(removedObject, mGameData);
			mGameData.removeGameObject(removedObject);
		}
	}
}

void ObjectStateUpdateSystem::createExplosionFor( GameObject_WithCollider * removedObject, GameData& mGameData )
{
	GameObjectType objectType = removedObject->getType();
	if (objectType == GameObjectType::effectObject || objectType == GameObjectType::bulletObject)
	{
		return;
	}
	unsigned effectId = removedObject->getExpolsionEffectID();
	EffectObject * effect = mGameData.instantiateEffect(effectId);
	effect->setPosition(removedObject->getPosition());
	return;
}

