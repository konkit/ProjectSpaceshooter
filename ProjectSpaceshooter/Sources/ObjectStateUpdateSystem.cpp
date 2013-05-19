#include "ObjectStateUpdateSystem.h"

void ObjectStateUpdateSystem::update( GameData& mGameData, TimeData& time )
{
	//for every gameobject
	//if one needs to be removed - remove it
	//if one needs to be created - create it

	removeDeadObjects(mGameData);
	
	updateShooting(mGameData);

	//spawning enemies
	mGameData.getLevelDescription().spawn(mGameData, time.currentTime);

	updateObjectWithTTL(mGameData, time);

}

void ObjectStateUpdateSystem::removeDeadObjects( GameData& mGameData)
{
	static int counter = 0;
	auto iterator = mGameData.getColidingObjectsIterator();
	GameObject_WithCollider * removedObject;
	iterator.skipPlayer();
	counter++;
	while (iterator.hasNext())
	{
		removedObject = iterator.getNext();
		if (removedObject->isDead())
		{
			createExplosionFor(removedObject, mGameData);
			mGameData.removeGameObject(iterator);
		}
	}
}

void ObjectStateUpdateSystem::createExplosionFor( GameObject_WithCollider * removedObject, GameData& mGameData )
{
	GameObjectType objectType = removedObject->getType();
	if (objectType == GameObjectType::effectObject)
	{
		return;
	}
	unsigned effectId = removedObject->getExpolsionEffectID();
	if (effectId == 0)
	{
		return; // Some objects may not have own explosion effect
	}
	EffectObject * effect = mGameData.instantiateEffect(effectId);
	effect->setPosition(removedObject->getPosition());
	effect->setOrientation(removedObject->getOrientation());
	return;
}

void ObjectStateUpdateSystem::destroyPlayer( GameData& mGameData)
{
	Player * player = mGameData.getPlayer();
	if (player != NULL)
	{
		createExplosionFor(player, mGameData);
		mGameData.destroyPlayer();
	} else
	{
		throw My_Exception("Try to remove nonexistent player");
	}
}

void ObjectStateUpdateSystem::updateShooting( GameData &mGameData )
{
	//creating bullets when player is shooting
	Player * player = mGameData.getPlayer();
	if (player != NULL)
	{
		serveShooting(player, mGameData);
	}

	//parsing through enemies
	GameCollectionIterator<EnemyObject> enemyIterator = mGameData.getEnemies().getIterator();
	EnemyObject* enemyIt;
	while (enemyIterator.hasNext())
	{
		enemyIt = enemyIterator.getNext();
		serveShooting(enemyIt, mGameData);
	}
}

void ObjectStateUpdateSystem::serveShooting( Ship * shooter, GameData &mGameData )
{
	if( shooter->isShooting() == true)	
	{
		//get player's data required to create new bullet
		Ogre::Quaternion playerOrientation = shooter->getOrientation();
		Ogre::Vector3 playerPos = shooter->getPosition();

		Bullet* newBullet = mGameData.instantiateBullet(shooter->getBulletIDFromActiveWeapon());
		//set player pos
		newBullet->setPosition(playerPos);
		//set player orientation
		newBullet->setOrientation(playerOrientation);
		//set owner
		newBullet->setOwner(shooter);
		//set time to live
		newBullet->getTTLComponent().setTimeToLive(3.0);
		//set speed
		newBullet->setTargetVelocity( Ogre::Vector3(0.0, 0.0, 1.0) );
		newBullet->setCurrentSpeedToMax();

		//set shooting as false
		shooter->unsetShoot();
	}
}

void ObjectStateUpdateSystem::updateObjectWithTTL( GameData &mGameData, TimeData &time )
{
	//deleting bullets when time to Live is up.
	GameCollectionIterator<Bullet> bulletIterator = mGameData.getBullets().getIterator();
	Bullet* bulletIt;
	while (bulletIterator.hasNext())
	{
		bulletIt = bulletIterator.getNext();

		bulletIt->getTTLComponent().decreaseTimeToLive(time.deltaTime);

	}



	GameCollectionIterator<EffectObject> effectIterator = mGameData.getEffects().getIterator();
	EffectObject* effectIt;
	while (effectIterator.hasNext())
	{
		effectIt = effectIterator.getNext();

		effectIt->getTTLComponent().decreaseTimeToLive(time.deltaTime);
	}
}



