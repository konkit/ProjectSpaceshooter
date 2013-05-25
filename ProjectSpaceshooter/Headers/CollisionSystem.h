#pragma once

#include "DebugDrawer.h"

//#define ALLCOLLIDERS true

#define SCORE_FOR_KILL 100

/** System which detects and resolves collisions 
  *
  * @author Zyga
  */
class CollisionSystem	{
public:
	CollisionSystem() : COLLISION_DAMAGE(5){}

	/** Method which resolves collisions in a posteriori way */
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
	
	/**
	* Check if type is equal static object or core
	* @return Return true if object is Static object or is the Core
	* @param GameObjectType currType
	* @author Zyga
	*/
	bool inline isStaticObject( GameObjectType currType );

	/**
	* Check if it is collision between bullet and bullet owner
	* @return True if type of bullet owner is the same as type of second parameter
	* @param GameObject_WithCollider * currentObject
	* @param GameObject_WithCollider * otherObject
	* @author Zyga
	*/
	bool isBulletAndOwner( GameObject_WithCollider * currentObject, GameObject_WithCollider * otherObject );
};
