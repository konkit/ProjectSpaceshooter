#pragma once

#include "GameObject.h"
#include "TimeToLiveComponent.h"

/** 
  *
  * @author konkit
  */
class BulletPrefab
{
	//Ja to ogarnê, spoko ;P - Konkit
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
