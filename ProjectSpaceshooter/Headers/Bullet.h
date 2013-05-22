#pragma once

#include "GameObject.h"
#include "TimeToLiveComponent.h"
#include "Prefabs.h"


/** Class of Bullet gameobject
  * 
  * @author konkit 
  */
class Bullet : public GameObject_WithCollider, public GameObject_Movable
{

public:
	/** Loads data of effect from prefab */
	Bullet::Bullet(const BulletPrefab * objectTemplate, Ogre::SceneManager * _sceneMenager);
	~Bullet();

	/** returns power of bullet
	  * @return unsigned - power of bullet
	  */
	unsigned getPower() const { return mPower; }

	/** sets new power of bullet */
	void setPower(unsigned val) { mPower = val; }

	/** sets owner of bullet */
	void setOwner(Ship* owner) {mOwnerType = owner->getType();}

	/** returns type of bullet 
	  * @return GameObjectType - type of owner object of bullet (player, enemy, etc...)
	  */
	GameObjectType getOwnerType() {return mOwnerType;}

	/** returns Time To Live component 
	  * @return TimeToLiveComponent
	  */
	TimeToLiveComponent& getTTLComponent();

	/** sets speed of bullet to max speed */
	void setCurrentSpeedToMax(Ogre::Vector3 forwardVector) { mPhysicsComponent.setCurrentSpeedToMax(forwardVector); }

	/** implementation of getType virtual method from GameObject class 
	  * @return GameObjectType - type of this object (in this case: bulletObject)
	  */
	GameObjectType getType() {
		return GameObjectType::bulletObject;
	}

	/** checks if bullet is dead
	  * @return bool - true if dead
	  */
	bool isDead() 
	{
		if( mTTLComponent.isTimeIsUp()==true )
			return true;
		return mDeadFlag;
	}

	/** returns ID of prefab (which type is this bullet) 
	  * @return unsigned - ID of the prefab
	  */
	unsigned getPrefabID() const {return prefabID;}

	//	virtual bool receiveDamage( unsigned int damages, Vector3 fromDirection = Vector3(0,0,0 )) {mDeadFlag = false;}

	/** resets bullet - set initial values */
	void resetBullet()
	{
		mTTLComponent.setTimeToLive(startTTL);
		mDeadFlag = false;
	}
private:
	unsigned mPower;
	unsigned prefabID;
	float startTTL;
	GameObjectType mOwnerType;
	TimeToLiveComponent mTTLComponent;

};
