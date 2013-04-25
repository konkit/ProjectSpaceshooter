#pragma once

#include "DebugDrawer.h"

//#define ALLCOLLIDERS true

class CollisionSystem	{
public:
	CollisionSystem() : COLLISION_DAMAGE(20){}
	//Method which resolves collisions
	//collisions are resolved a posteriori
	void update(GameData& mGameData);

	void drawColiderDebug( GameObject_WithCollider * obj );

	void CheckForCollisions( GameObject_WithCollider * currentObject, GameData::ColidingObjectsIterator it ,GameData& mGameData);
	void servCollisionBetween( GameObject_WithCollider * currentObject, GameObject_WithCollider * tmp );

	//It is a damages resulting collision with object having weight
	const unsigned COLLISION_DAMAGE;
private:
	bool collisionWithStatic( GameObject_WithCollider * currentObject, GameObject_WithCollider * otherObject );
	bool collisionWithBullet( GameObject_WithCollider * currentObject, GameObject_WithCollider * otherObject );
	bool collisionWithExplosion( GameObject_WithCollider * currentObject, GameObject_WithCollider * otherObject );
	bool collisionBetweenShips( GameObject_WithCollider * currentObject, GameObject_WithCollider * otherObject );

	bool inline isShip( GameObjectType currType );
	bool isBulletAndOwner( GameObject_WithCollider * currentObject, GameObject_WithCollider * otherObject );
};
