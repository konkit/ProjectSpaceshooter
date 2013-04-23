#pragma once

#include "GameObject.h"
#include "TimeToLiveComponent.h"
#include "Prefabs.h"


/** Class of Bullet gameobject
  * 
  * @author konkit 
  */
class Bullet : public GameObject_WithColider, public GameObject_Movable
{

public:
	Bullet();

	Bullet(std::string meshName, Ogre::SceneManager* sceneMgr);

	Bullet::Bullet(const BulletPrefab * objectTemplate, Ogre::SceneManager * _sceneMenager);

	unsigned getPower() const { return mPower; }
	void setPower(unsigned val) { mPower = val; }

	void setOwner(GameObject* owner);
	GameObject* getOwner();

	TimeToLiveComponent& getTTLComponent();

	void setCurrentSpeedToMax() { mPhysicsComponent.setCurrentSpeedToMax(); }

	GameObjectType getType() {
		return GameObjectType::bulletObject;
	}

	virtual bool receiveDamage( unsigned int damages ) {return mDeadFlag = true;};

	virtual void hit( GameObject_WithColider * tmp ){tmp->receiveDamage(mPower, getPosition());}
	bool isDead() 
	{
		if( mTTLComponent.isTimeIsUp()==true )
			return true;
		return mDeadFlag;
	}
private:
	unsigned mPower;
	GameObject* mOwner;
	TimeToLiveComponent mTTLComponent;
};
