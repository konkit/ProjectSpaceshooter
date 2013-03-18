#pragma once

#include "PhysicsComponent.h"
#include "GamelogicComponent.h"
#include "ColliderComponent.h"

#include <string>
enum  class GameObjectType 
{
	player,
	enemyObject,
	bulletObject,
	staticObject,
	physicObject
};

enum class AI_TYPE
{
	fighter,
	defender
};

/** Game object class
  * Game objects represents object in gameworld - enemies, bullets etc.
  * Those are composed from components (physics component, gamelogiccomponent, etc.)
  * This is abstract class - Bullet, Enemy and other classes inherit from this class
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

	GamelogicComponent& getGamelogicComponent() {
		return mGamelogicComponent;
	}

	//Manipulations on Ogre::SceneNode
	void createSceneNode(std::string meshName, Ogre::SceneManager* sceneMgr);
	Ogre::SceneNode* getSceneNode()	{	return mNode;	}

	void setPosition(Ogre::Vector3 newPos)	{	mNode->setPosition(newPos); }
	Ogre::Vector3 getPosition()	{	return mNode->getPosition(); }

	void setOrientation(Ogre::Quaternion newOrientation)	{	mNode->setOrientation(newOrientation);	}
	Ogre::Quaternion getOrientation()	{	return mNode->getOrientation();	}

	void move(Ogre::Vector3 nPos) {		mNode->translate( mNode->getOrientation() * nPos );	}
	void rotate(float rotVelocity)	{	mNode->yaw( Ogre::Radian(rotVelocity) ); }

protected:
	GameObjectType mObjectType;
	PhysicsComponent mPhysicsComponent;
	GamelogicComponent mGamelogicComponent;
	Collider mColliderComponent;

	Ogre::SceneNode* mNode;

	


};

