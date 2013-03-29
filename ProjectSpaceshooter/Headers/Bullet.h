#pragma once

#include "GameObject.h"
#include "TimeToLiveComponent.h"

/** 
  *
  * @author konkit
  */
class BulletPrefab
{
public:
	BulletPrefab(unsigned prefabID) : mPrefabID(prefabID)
	{	}

	void setPrefabID(unsigned val) { mPrefabID = val; }
	void setMeshName(string val) { mMeshName = val; }
	void setBulletPower(float newPower) { bulletPower = newPower; }
	void setMaxVelocity(float newMaxVelocity) { mMaxVelocity= newMaxVelocity; }
	void setVelocityVector( Ogre::Vector3 newVector){ mVelocityVector = newVector; }

	unsigned	 getPrefabID()   const { return mPrefabID; }
	std::string	 getMeshName()	  const { return mMeshName; }
	float		 getBulletPower() const { return bulletPower; }
	float		 getMaxVelocity() const { return mMaxVelocity; }
	Ogre::Vector3 getVelocityVector() const { return mVelocityVector; }
private:
	unsigned	mPrefabID;
	string		mMeshName;
	float		bulletPower;
	float		mMaxVelocity;
	Ogre::Vector3 mVelocityVector;
};

/** Class of Bullet gameobject
  * 
  * @author konkit 
  */
class Bullet : public GameObject	{

public:
	Bullet() : GameObject()
	{
		mTTLComponent.setTimeToLive(3000);
	}

	Bullet(std::string meshName, Ogre::SceneManager* sceneMgr) : GameObject(meshName, sceneMgr)	
	{
		mTTLComponent.setTimeToLive(3000);
	}

	Bullet::Bullet( BulletPrefab * objectTemplate, Ogre::SceneManager * _sceneMenager)
		: GameObject(objectTemplate->getMeshName(), _sceneMenager), 
		  mPower(objectTemplate->getBulletPower())

	{
		mPhysicsComponent.setMaxVelocityValue( objectTemplate->getMaxVelocity() );
		mPhysicsComponent.setVelocity( objectTemplate->getVelocityVector() );
		mTTLComponent.setTimeToLive(3000);
	}



	float getPower()
	{
		return mPower;
	}

	void setPower(float newPower)
	{
		mPower = newPower;
	}

	void setOwner(GameObject* owner)
	{
		mOwner = owner;
	}

	bool isDead() {
		if( mTTLComponent.isTimeIsUp()==true )
			return true;
		if( GameObject::isDead() == true )
			return true;

		return false;
	}

	TimeToLiveComponent& getTTLComponent()	{
		return mTTLComponent;
	}

private:
	float mPower;
	GameObject* mOwner;
	TimeToLiveComponent mTTLComponent;
};
