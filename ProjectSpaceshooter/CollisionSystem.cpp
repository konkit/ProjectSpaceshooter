
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
				if(!isBulletAndOwner(currentObject, otherObject))
					if (currentObject->isColidingWith(otherObject))
					{
						servCollisionBetween(currentObject, otherObject);
#ifdef _DEBUG
						std::cout << "Collision between " << ObjectTypeToString(curr) << " and " << ObjectTypeToString(oth) << endl;
#endif			
					}
		}
	}
}

void CollisionSystem::servCollisionBetween( GameObject_WithCollider * currentObject, GameObject_WithCollider * otherObject )
{
	if (collisionWithStatic(currentObject, otherObject))
	{
		return;
	} else if(collisionWithBullet(currentObject, otherObject))
	{
		return;
	} else if(collisionWithExplosion(currentObject, otherObject))
	{
		return;	
	} else if(collisionBetweenShips(currentObject, otherObject))
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
		//switch object, I assume that Bullet Object is in variable currentObject
		if (currType != GameObjectType::staticObject)
		{
			tmp = currentObject;			tmptype  = currType;
			currentObject = otherObject;	currType = othType;
			otherObject = tmp;				othType  = tmptype;
		} 

		Bullet * bullet = dynamic_cast<Bullet *>(currentObject);
		if(isShip(othType))
		{
			Ship * owner = bullet->getOwner();
			if (owner->getType() == othType)
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
	if (currType == GameObjectType::staticObject || othType == GameObjectType::staticObject)
	{
		//switch object, I assume that Static Object is in variable currentObject
		if (currType != GameObjectType::staticObject)
		{
			tmp = currentObject;			tmptype  = currType;
			currentObject = otherObject;	currType = othType;
			otherObject = tmp;				othType  = tmptype;
		} 

		if (othType == GameObjectType::staticObject)
		{
			currentObject->kill();
			otherObject->kill();
		} else if(othType == GameObjectType::enemyObject || othType == GameObjectType::player)
		{
			Ship * ship;
			unsigned velocity;
			ship = dynamic_cast<Ship*>(otherObject);
			velocity = ship->getPhysicsComponent().getCurrentVelocityValue();
			currentObject->receiveDamage(COLLISION_DAMAGE * velocity);
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
		//switch object, I assume that Bullet Object is in variable currentObject
		if (currType != GameObjectType::bulletObject)
		{
			tmp = currentObject;			tmptype  = currType;
			currentObject = otherObject;	currType = othType;
			otherObject = tmp;				othType  = tmptype;
		} 

		if (othType != GameObjectType::effectObject)
		{
			Bullet * bullet = dynamic_cast<Bullet *>(currentObject);
			unsigned damages = bullet->getPower();
			currentObject->receiveDamage(damages); // Value is irrelevant because bullet immediately explode
			otherObject->receiveDamage(damages, currentObject->getPosition()); // Don't care if it's other bullet - he explode;
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

		EffectObject * effect = dynamic_cast<EffectObject *>(currentObject);
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
		DebugDrawer::getSingleton().drawCircle(coli.offset, coli.radius, 25, Ogre::ColourValue(1.0f, 0.0f, 0.0f) );
	}
#endif // ALLColliderS
}

bool CollisionSystem::isShip( GameObjectType currType )
{
	return currType == GameObjectType::enemyObject || currType == GameObjectType::player;
}


