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
using std::string;
string ObjectTypeToString(GameObjectType type);

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

	void setMesh(const PrefabWithMesh * prefab,  Ogre::SceneManager* sceneMgr);
	virtual bool isDead() = 0;

	void move(Ogre::Vector3 nPos) {		mNode->translate( nPos );	}
	void rotate(float rotVelocity)	{	mNode->yaw( Ogre::Radian(rotVelocity) ); }

	virtual GameObjectType getType() = 0;

protected:
	GameObjectType mObjectType;
	Ogre::SceneNode* mNode;
	static unsigned uniqueID;
};


class GameObject_WithCollider : virtual public GameObject
{
public:
	GameObject_WithCollider() : mDeadFlag(false), mCollider()
	{
		Collider_struct tmp;
		tmp.offset = Vector3(0,0,0);
		tmp.radius = 20;
		mCollider.addCollider(tmp);
		mExpolsionEffectID = 1;
	}
	GameObject_WithCollider(const PrefabWithCollider * prefab, Ogre::SceneManager* sceneMgr);
	virtual ~GameObject_WithCollider(){}

	void setColliderFromPrefab(const PrefabWithCollider * prefab)
	{
		mCollider.reset();
		mCollider = prefab->getCollider();
		mExpolsionEffectID = prefab->getExplosionEffectID();
	}

	virtual GameObjectType getType() = 0;

	/**
	* Method take value of damages which should subtract from health
	* If object don't have health, he died immediately
	* @return bool - if object die return true
	* @param unsigned int damages - value of damages
	* @author Zyga
	*/

	virtual bool receiveDamage(unsigned int damages, Vector3 fromDirection = Vector3(0,0,0)){return mDeadFlag = true;}
	bool isDead(){return mDeadFlag;}
	bool kill() {return mDeadFlag = true;}

	bool isColidingWith( GameObject_WithCollider * _object );
	const Collider & getCollider() const {return mCollider;}
	unsigned getExpolsionEffectID() const { return mExpolsionEffectID; }
	void setExpolsionEffectID(unsigned val) { mExpolsionEffectID = val; }
	
protected:
	bool mDeadFlag;
private:
	Collider mCollider;
	unsigned mExpolsionEffectID;
};

class GameObject_WithHealth : public GameObject_WithCollider
{
public:
	GameObject_WithHealth() : mHealth() {;}
	GameObject_WithHealth(const PrefabWithCollider * prefab, Ogre::SceneManager* sceneMgr);
	virtual ~GameObject_WithHealth() {;}
	
	virtual bool receiveDamage( unsigned int damages, Vector3 fromDirection = Vector3(0,0,0)) 
	{
		mHealth.decreaseHealth(damages);
#ifdef _DEBUG
		std::cout << ObjectTypeToString(getType()) << ": remained health = " << mHealth.getHealth() << endl;
#endif
		return mDeadFlag = mHealth.isDead();
	}

	bool isDead() {
		return mDeadFlag;
	}

	void setDead() {
		mDeadFlag = true;
	}
	
	void setHealthAndColliderFromPrefab(const PrefabWithCollider * prefab)
	{
		setColliderFromPrefab(prefab);
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
	void setCurrentSpeedToMax() { mPhysicsComponent.setCurrentSpeedToMax(); }
	void addRecoilVectorToCurrentVelocity(Vector3 recoil) 
	{
		mPhysicsComponent.AddVectorToCurrentVelocity(recoil);
	}

protected:
	PhysicsComponent mPhysicsComponent;
};