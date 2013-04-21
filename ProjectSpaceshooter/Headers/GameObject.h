#pragma once

#include "PhysicsComponent.h"
#include "ColliderComponent.h"

#include <string>

enum  class GameObjectType 
{
	player,
	core,
	enemyObject,
	bulletObject,
	staticObject,
	physicObject,
	effectObject
};



/** Game object class
  * Game objects represents object in gameworld - enemies, bullets etc.
  * Those are composed from components (physics component, gamelogiccomponent, etc.)
  * This is abstract class - Bullet, Enemy and other classes inherit from this class
  *
  * 
  * 
  * @author 
  */
class GameObject 
{
public:
	GameObject();
	GameObject(std::string meshName, Ogre::SceneManager* sceneMgr);
	virtual ~GameObject(void);

	PhysicsComponent& getPhysicsComponent()	{
		return mPhysicsComponent;
	}

	Collider& getCollider()	{
		return mCollider;
	}

	//Manipulations on Ogre::SceneNode
	void createSceneNode(std::string meshName, Ogre::SceneManager* sceneMgr);
	Ogre::SceneNode* getSceneNode()	{	return mNode;	}

	void setPosition(Ogre::Vector3 newPos)	{	
		mNode->setPosition(newPos); 
	}

	Ogre::Vector3 getPosition()	{	
		return mNode->getPosition(); 
	}

	void setOrientation(Ogre::Quaternion newOrientation)	{	
		mNode->setOrientation(newOrientation);	
	}
	Ogre::Quaternion getOrientation()	{	
		return mNode->getOrientation();	
	}

	void setTargetVelocity( Ogre::Vector3 localDirection ) {
		mPhysicsComponent.setTargetVelocity( mNode->getOrientation(), localDirection );
	}

	void addVectorToCurrentVelocity( Ogre::Vector3 addedVector ) {
		mPhysicsComponent.AddVectorToCurrentVelocity(  mNode->getOrientation() * addedVector  );
	}

	void move(Ogre::Vector3 nPos) {		mNode->translate( nPos );	}
	void rotate(float rotVelocity)	{	mNode->yaw( Ogre::Radian(rotVelocity) ); }

	bool isDead() {
		return mDeadFlag;
	}

	void setDead() {
		mDeadFlag = true;
	}

	virtual GameObjectType getType() = 0;

protected:
	GameObjectType mObjectType;
	PhysicsComponent mPhysicsComponent;
	Collider mCollider;

	Ogre::SceneNode* mNode;

	bool mDeadFlag;

	


};

