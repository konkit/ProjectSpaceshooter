#pragma once

#include "PhysicsComponent.h"
#include "ColliderComponent.h"
#include "HealthComponent.h"
#include "Prefabs.h"

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
	GameObject(const PrefabWithMesh * prefab, Ogre::SceneManager* sceneMgr); 
	virtual ~GameObject(void);

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

	position_struct getPositionAndOrientation() const 
	{
		position_struct tmp;
		tmp.orientation = mNode->getOrientation();
		tmp.position = mNode->getPosition();
		return tmp;
	}


	void move(Ogre::Vector3 nPos) {		mNode->translate( nPos );	}
	void rotate(float rotVelocity)	{	mNode->yaw( Ogre::Radian(rotVelocity) ); }

	position_struct getObjectPosition(); 
protected:
	GameObjectType mObjectType;
	Ogre::SceneNode* mNode;
};


class GameObject_WithColider : virtual public GameObject
{
public:
	GameObject_WithColider() : mDeadFlag(false), mColider()
	{
		colider_struct tmp;
		tmp.offset = Vector3(0,0,0);
		tmp.radius = 20;
		mColider.addColider(tmp);
	}
	GameObject_WithColider(const PrefabWithColider * prefab, Ogre::SceneManager* sceneMgr);
	virtual ~GameObject_WithColider(){;}

	void setColiderFromPrefab(const PrefabWithColider * prefab)
	{
		mColider.reset();
		mColider = prefab->getColider();
	}

	virtual GameObjectType getType() = 0;

	/**
	* When object is hit by other object, object kill other object or takes him life if this is object is bullet
	* @return void
	* @param GameObject * tmp - object to hit
	* @author Zyga
	*/
	virtual void hit( GameObject_WithColider * tmp ) {tmp->kill();}

	/**
	* Method take value of damages which should subtract from health
	* If object don't have health, he died immediately
	* @return bool - if object die return true
	* @param unsigned int damages - value of damages
	* @author Zyga
	*/
	virtual bool receiveDamage(unsigned int damages, Vector3 fromDirection){return mDeadFlag = true;}
	bool isDead(){return mDeadFlag;}
	virtual bool kill(){mDeadFlag = true; return mDeadFlag;}
	bool isColidingWith( GameObject_WithColider * _object );
	const Collider & getColider() const {return mColider;}
protected:
	bool mDeadFlag;
private:
	Collider mColider;
};

class GameObject_WithHealth : public GameObject_WithColider
{
public:
	GameObject_WithHealth() : mHealth() {;}
	GameObject_WithHealth(const PrefabWithColider * prefab, Ogre::SceneManager* sceneMgr);
	virtual ~GameObject_WithHealth() {;}
	
	virtual bool receiveDamage( unsigned int damages, Vector3 fromDirection) 
	{
		mHealth.decreaseHealth(damages);
		return mDeadFlag = mHealth.isDead();
	}

	bool isDead() {
		return mDeadFlag;
	}

	void setDead() {
		mDeadFlag = true;
	}
	
	void setHealthAndColiderFromPrefab(const PrefabWithColider * prefab)
	{
		setColiderFromPrefab(prefab);
		mHealth.setHealthFromPrefab(prefab);
	}

private:
	HealthComponent mHealth;
};

class GameObject_Movable : virtual public GameObject
{
public:
	GameObject_Movable(){;}
	GameObject_Movable(const MovablePrefab * prefab, Ogre::SceneManager* sceneMgr);
	virtual ~GameObject_Movable(){;}
	void setPhysicsFromPrefab(const MovablePrefab * prefab)
	{
		mPhysicsComponent.setFromPrefab(prefab);
	}

	void move(Ogre::Vector3 nPos) {		mNode->translate( nPos );	}
	void rotate(float rotVelocity)	{	mNode->yaw( Ogre::Radian(rotVelocity) ); }
	void setTargetVelocity( Ogre::Vector3 localDirection ) {
		mPhysicsComponent.setTargetVelocity( mNode->getOrientation(), localDirection );
	}
	PhysicsComponent& getPhysicsComponent()	{
		return mPhysicsComponent;
	}
	void setMaxSpeed() { mPhysicsComponent.setMaxSpeed(); }
protected:
	PhysicsComponent mPhysicsComponent;
};