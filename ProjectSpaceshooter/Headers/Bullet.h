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
	Bullet();

	Bullet(std::string meshName, Ogre::SceneManager* sceneMgr);

	Bullet::Bullet(const BulletPrefab * objectTemplate, Ogre::SceneManager * _sceneMenager);

	~Bullet();
	unsigned getPower() const { return mPower; }
	void setPower(unsigned val) { mPower = val; }

	void setOwner(Ship* owner) {mOwner = owner;}
	Ship* getOwner() {return mOwner;}

	TimeToLiveComponent& getTTLComponent();

	void setCurrentSpeedToMax() { mPhysicsComponent.setCurrentSpeedToMax(); }

	GameObjectType getType() {
		return GameObjectType::bulletObject;
	}


	bool isDead() 
	{
		if( mTTLComponent.isTimeIsUp()==true )
			return true;
		return mDeadFlag;
	}

//	virtual bool receiveDamage( unsigned int damages, Vector3 fromDirection = Vector3(0,0,0 )) {mDeadFlag = false;}

private:
	unsigned mPower;
	Ship* mOwner;
	TimeToLiveComponent mTTLComponent;
};
