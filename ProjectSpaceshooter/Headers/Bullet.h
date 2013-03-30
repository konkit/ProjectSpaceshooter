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
	BulletPrefab(unsigned prefabID);

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
	Bullet();

	Bullet(std::string meshName, Ogre::SceneManager* sceneMgr);

	Bullet::Bullet( BulletPrefab * objectTemplate, Ogre::SceneManager * _sceneMenager);

	float getPower();
	void setPower(float newPower);

	void setOwner(GameObject* owner);

	bool isDead();

	TimeToLiveComponent& getTTLComponent();

private:
	float mPower;
	GameObject* mOwner;
	TimeToLiveComponent mTTLComponent;
};
