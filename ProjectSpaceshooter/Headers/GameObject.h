#pragma once

#include "PhysicsComponent.h"
#include "ColliderComponent.h"
#include "HealthComponent.h"
#include "Prefabs.h"

#include <string>


/** enum type storing information about type of game object */
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

		/** returns the Ogre::SceneNode of this specific GameObject */
		Ogre::SceneNode* getSceneNode()	{	return mNode;	}

	//Manipulations on position and orientation of Game Object
		/** sets new position of Game Object */
		void setPosition(Ogre::Vector3 newPos)	{	mNode->setPosition(newPos); }

		/** returns Ogre::Vector3 with current position of the game object */
		Ogre::Vector3 getPosition()	{	return mNode->getPosition(); 	}

		/** sets new orientation of game object */
		void setOrientation(Ogre::Quaternion newOrientation)	{	mNode->setOrientation(newOrientation);	}
		
		/** returns the Ogre::Quaternion with current orientation of the object */
		Ogre::Quaternion getOrientation()	{	return mNode->getOrientation();	}

		/** returns Ogre::Vector3 with vector pointing forward from the game object */
		Ogre::Vector3 getForwardVector()	{
			return mNode->getOrientation() * Ogre::Vector3(0.0, 0.0, 1.0);
		}

		/** returns position and orientation of the game object */
		position_struct getPositionAndOrientation() const 
		{
			position_struct tmp;
			tmp.orientation = mNode->getOrientation();
			tmp.position = mNode->getPosition();
			return tmp;
		}

	/** sets mesh and all data from specified prefab */
	void setMesh(const PrefabWithMesh * prefab,  Ogre::SceneManager* sceneMgr);

	/** virtual method is dead - implemented differently depending on certain game object */
	virtual bool isDead() = 0;

	/** translate current position by vector */
	void move(Ogre::Vector3 nPos) {		mNode->translate( nPos );	}

	/** rotate the game object by specified angle in radians */
	void rotate(float rotVelocity)	{	mNode->yaw( Ogre::Radian(rotVelocity) ); }

	/** virtual method getType returning type of the specific game object */
	virtual GameObjectType getType() = 0;

	/** sets if game object should be visible or not */
	void setVisible( bool visibility ) {mNode->setVisible(visibility);}

protected:
	GameObjectType mObjectType;
	Ogre::SceneNode* mNode;
	static unsigned uniqueID;
};

/** Game object with collider component
  * this object takes part in collision detection 
  *
  * @author
  */
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

/** Game object with health and collider components
  * this object can be destroyed if health is below zero
  * collisions with this objects affects the health
  *
  * @author
  */
class GameObject_WithHealth : public GameObject_WithCollider
{
public:
	GameObject_WithHealth() : mHealth() {;}
	GameObject_WithHealth(const PrefabWithCollider * prefab, Ogre::SceneManager* sceneMgr);
	virtual ~GameObject_WithHealth() {;}
	
	virtual bool receiveDamage( unsigned int damages, Vector3 fromDirection = Vector3(0,0,0)) 
	{
		mHealth.decreaseHealth(damages);
//#ifdef _DEBUG
//		std::cout << ObjectTypeToString(getType()) << ": remained health = " << mHealth.getHealth() << endl;
//#endif
		return mDeadFlag = mHealth.isDead();
	}

	/** Check if object is dead 
	  * @return bool - true if dead
	  */
	bool isDead() {
		return mDeadFlag;
	}

	/** Mark object as dead */
	void setDead() {
		mDeadFlag = true;
	}
	
	/** Loads data from prefab to Collider and Health components */
	void setHealthAndColliderFromPrefab(const PrefabWithCollider * prefab)
	{
		setColliderFromPrefab(prefab);
		mHealth.setHealthFromPrefab(prefab);
	}

	/** returns current health value */
	int getHealthValue()	{
		return mHealth.getHealth();
	}

	/** returns maximum health value */
	int getMaxHealthValue()	{
		return mHealth.getMaxHealth();
	}

private:
	HealthComponent mHealth;
};


/** Game object with physics component
  * Such objects are movable in game - have certain velocity vector, acceleration etc.
  *
  * @author
  */
class GameObject_Movable : virtual public GameObject
{
public:
	GameObject_Movable(){;}
	GameObject_Movable(const MovablePrefab * prefab, Ogre::SceneManager* sceneMgr);
	virtual ~GameObject_Movable(){;}

	/** Load data from prefab to physics component */
	void setPhysicsFromPrefab(const MovablePrefab * prefab)
	{
		mPhysicsComponent.setFromPrefab(prefab);
	}

	/** translate object's positoin by specified vector */
	void move(Ogre::Vector3 nPos) {		mNode->translate( nPos );	}

	/** update rotation by specified angle velocity.
	  * The value of angle velocity affects the Roll angle.
	  */
	void rotate(float rotVelocity, float deltaTime)	{	
		//get current value of yaw angle
		Ogre::Radian yaw = mNode->getOrientation().getYaw();
		//count value of roll angle 
		Ogre::Radian roll =  Ogre::Radian( Ogre::Degree(rotVelocity * -10.0) );

		//reset orientation data of current node
		mNode->resetOrientation();

		//get roll rotation quaternion
		Ogre::Quaternion targetRoll( roll, Ogre::Vector3::UNIT_Z );
		//get yaw rotation quaternion
		Ogre::Quaternion targetYaw( yaw + Ogre::Radian( rotVelocity * deltaTime), Ogre::Vector3::UNIT_Y );

		//set new quaternion
		mNode->setOrientation( targetYaw * targetRoll );
	}

	/** Sets target velocity value (to which current velocity approaches ) */
	void setTargetVelocityValue( float value ) {
		mPhysicsComponent.setTargetVelocityValue( value );
	}

	/** This method is run in Input Manager 
	  * Depending on boolean values forward and backward, 
	  * target velocity value is increased or decreased
	  */
	void setMovement(bool forward, bool backward, float deltaTime)	{
		float value;
		if( forward == true)	
			value = 1000.0 * deltaTime;
		if( backward == true)
			value = -1000.0 * deltaTime;
		
		mPhysicsComponent.increaseTargetVelocityValue(value);
	}

	/** This method is run in Input Manager 
	  * Depending on boolean values forward and backward, 
	  * target rot velocity is set on positive or negative value
	  */
	void setRotation(bool clockwise, bool counterClockwise)	{
		float value = 0.0;
		if( counterClockwise == true)	
			value = 1.0;
		if( clockwise == true)
			value = -1.0;

		mPhysicsComponent.setTargetRotVelocity( value );
	}


	PhysicsComponent& getPhysicsComponent()	{
		return mPhysicsComponent;
	}

	/** sets current velocity to maximal */
	void setCurrentSpeedToMax(Ogre::Vector3 forwardVector) { mPhysicsComponent.setCurrentSpeedToMax(forwardVector); }

	/** add recoil force to current velocity */
	void addRecoilVectorToCurrentVelocity(Vector3 recoil) 
	{
		recoil.y = 0; // To avoid vertical movement
		mPhysicsComponent.AddVectorToCurrentVelocity(recoil);
	}

	/**    */
	void createThrusters(const MovablePrefab * _prefab, Ogre::SceneManager * _sceneMenager );

protected:
	PhysicsComponent mPhysicsComponent;
	Ogre::SceneNode * mThrusterNode;
};