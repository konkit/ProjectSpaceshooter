#include "CollisionSystem.h"

void CollisionSystem::update( GameData& mGameData )
{
	GameData::ColidingObjectsIterator it = mGameData.getColidingObjectsIterator();
	GameObject_WithCollider * obj;

	while (it.hasNext())
	{
		obj = it.getNext();
		CheckForCollisions(obj, it ,mGameData);

#ifdef _DEBUG
		drawColiderDebug(obj);
#endif
	}
}

void CollisionSystem::CheckForCollisions( GameObject_WithCollider * currentObject, GameData::ColidingObjectsIterator it ,GameData& mGameData )
{
	GameObjectType curr, oth;
	GameObject_WithCollider * otherObject;
	while(it.hasNext())
	{
		otherObject = it.getNext();
		if (otherObject != currentObject)
		{
			curr = currentObject->getType(); 
			oth =  otherObject->getType();

			if(!(curr == GameObjectType::effectObject && oth == GameObjectType::effectObject)) // Checking collision between two effect haven't sense because nothing happened
				if(!isBulletAndOwner(currentObject, otherObject)) // Don't check collision if it is collision between bullet and bullet owner
					if (currentObject->isColidingWith(otherObject))
					{
						servCollisionBetween(currentObject, otherObject);
//#ifdef _DEBUG
//						std::cout << "Collision between " << ObjectTypeToString(curr) << " and " << ObjectTypeToString(oth) << endl;
//#endif			
					}
		}
	}
}

void CollisionSystem::servCollisionBetween( GameObject_WithCollider * currentObject, GameObject_WithCollider * otherObject )
{
	if (collisionWithBullet(currentObject, otherObject))
	{
		return;
	} else if(collisionBetweenShips(currentObject, otherObject))
	{
		return;
	} else if(collisionWithExplosion(currentObject, otherObject))
	{
		return;	
	} else if(collisionWithStatic(currentObject, otherObject))
		return;
	return;
}

bool CollisionSystem::isBulletAndOwner( GameObject_WithCollider * currentObject, GameObject_WithCollider * otherObject )
{
	GameObjectType currType, othType, tmptype;
	currType = currentObject->getType();
	othType = otherObject->getType();
	GameObject_WithCollider * tmp;

	if (currType == GameObjectType::bulletObject || othType == GameObjectType::bulletObject)
	{
		//switch object, I assume that Bullet Object is in variable 'currentObject'
		if (currType != GameObjectType::bulletObject)
		{
			tmp = currentObject;			tmptype  = currType;
			currentObject = otherObject;	currType = othType;
			otherObject = tmp;				othType  = tmptype;
		} 

		Bullet * bullet = static_cast<Bullet *>(currentObject);
		if(isShip(othType))
		{
			GameObjectType ownerType = bullet->getOwnerType();
			if (ownerType == othType)
			{
				return true;
			}
		}
	} 
	return false;

}

bool CollisionSystem::collisionWithStatic( GameObject_WithCollider * currentObject, GameObject_WithCollider * otherObject )
{
	GameObjectType currType, othType, tmptype;
	currType = currentObject->getType();
	othType = otherObject->getType();
	GameObject_WithCollider * tmp;
	if (isStaticObject(currType) || isStaticObject(othType))
	{
		//switch object, I assume that Static Object is in variable 'currentObject'
		if (!isStaticObject(currType))
		{
			tmp = currentObject;			tmptype  = currType;
			currentObject = otherObject;	currType = othType;
			otherObject = tmp;				othType  = tmptype;
		} 

		if (isStaticObject(othType))
		{
			currentObject->kill();
			otherObject->kill();
		} else if(othType == GameObjectType::enemyObject || othType == GameObjectType::player)
		{
			Ship * ship;
			unsigned velocity;
			ship = static_cast<Ship*>(otherObject);
			velocity = ship->getPhysicsComponent().getCurrentVelocityMagnitude();
			currentObject->receiveDamage(COLLISION_DAMAGE * velocity / 10);
			otherObject->kill();
		} else
		{
			return false;
		}
		return true;
	} else
	{
		return false;
	}
}

bool CollisionSystem::collisionWithBullet( GameObject_WithCollider * currentObject, GameObject_WithCollider * otherObject )
{
	GameObjectType currType, othType, tmptype;
	currType = currentObject->getType();
	othType = otherObject->getType();
	GameObject_WithCollider * tmp;

	if (currType == GameObjectType::bulletObject || othType == GameObjectType::bulletObject)
	{
		//switch object, I assume that Bullet Object is in variable 'currentObject'
		if (currType != GameObjectType::bulletObject)
		{
			tmp = currentObject;			tmptype  = currType;
			currentObject = otherObject;	currType = othType;
			otherObject = tmp;				othType  = tmptype;
		} 

		if (othType != GameObjectType::effectObject)
		{
			Bullet * bullet = static_cast<Bullet *>(currentObject);
			unsigned damages = bullet->getPower();
			currentObject->receiveDamage(damages); // Value is irrelevant because bullet immediately explode
			bool isDead = otherObject->receiveDamage(damages, currentObject->getPosition()); // Don't care if it's other bullet - he explode;

			//If player shot this bullet, then score is added
			if(isDead == true && bullet->getOwnerType() == GameObjectType::player && othType != GameObjectType::bulletObject)	{
				dynamic_cast<Player*>( bullet->getOwner() )->addScore( SCORE_FOR_KILL );
			}

		} 
		return true;
	} else
	{
		return false;
	}
}

bool CollisionSystem::collisionWithExplosion( GameObject_WithCollider * currentObject, GameObject_WithCollider * otherObject )
{
	GameObjectType currType, othType, tmptype;
	currType = currentObject->getType();
	othType = otherObject->getType();
	GameObject_WithCollider * tmp;

	if (currType == GameObjectType::effectObject || othType == GameObjectType::effectObject)
	{
		//switch object, I assume that Effect Object is in variable currentObject
		if (currType != GameObjectType::effectObject)
		{
			tmp = currentObject;			tmptype  = currType;
			currentObject = otherObject;	currType = othType;
			otherObject = tmp;				othType  = tmptype;
		} 

		EffectObject * effect = static_cast<EffectObject *>(currentObject);
		unsigned damages = effect->getPower();
		otherObject->receiveDamage(damages); // It can't be other explosion because collision between explosion isn't checked
		return true;
	} else
	{
		return false;
	}
}

bool CollisionSystem::collisionBetweenShips( GameObject_WithCollider * currentObject, GameObject_WithCollider * otherObject )
{
	GameObjectType currType, othType, tmptype;
	currType = currentObject->getType();
	othType = otherObject->getType();
	GameObject_WithCollider * tmp;

	if (isShip(currType) && isShip(othType))
	{
// TODO: remove this when enemy stop colliding both
		if (currType == othType)
		{
			return true;
		}
		currentObject->kill();
		otherObject->kill();
		return true;
	} else
	{
		return false;
	}
}



void CollisionSystem::drawColiderDebug( GameObject_WithCollider * obj )
{
	Collider_struct coli;
	position_struct pos;
	coli = obj->getCollider().getInaccurateCollider();
	pos = obj->getPositionAndOrientation();
	coli.offset = (pos.orientation * coli.offset) + pos.position;
	DebugDrawer::getSingleton().drawCircle(coli.offset, coli.radius, 25, Ogre::ColourValue(1.0f, 1.0f, 1.0f) );

#ifdef ALLCOLLIDERS
	Collider _Collider	= obj->getCollider();
	list<Collider_struct>::const_iterator coli_IT = _Collider.getCollidersBegin();
	list<Collider_struct>::const_iterator coli_end = _Collider.getCollidersEnd();

	for ( ; coli_IT != coli_end; coli_IT++)
	{
		coli = *coli_IT;
		pos = obj->getPositionAndOrientation();
		coli.offset = (pos.orientation * coli.offset) + pos.position;
		DebugDrawer::getSingleton().drawCircle(coli.offset, coli.radius, 25, Ogre::ColourValue(0.6f, 0.0f, 0.0f) );
//		DebugDrawer::getSingleton().drawSphere(coli.offset, coli.radius, Ogre::ColourValue(0.7f, 0.7f, 0.0f), false);
	}
#endif // ALLColliderS
}

bool CollisionSystem::isShip( GameObjectType currType )
{
	return currType == GameObjectType::enemyObject || currType == GameObjectType::player;
}

bool CollisionSystem::isStaticObject( GameObjectType currType )
{
	return (currType == GameObjectType::staticObject || currType == GameObjectType::core);
}


