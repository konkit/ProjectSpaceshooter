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

	Bullet::Bullet(const BulletPrefab * objectTemplate, Ogre::SceneManager * _sceneMenager);

	~Bullet();
	unsigned getPower() const { return mPower; }
	void setPower(unsigned val) { mPower = val; }

	void setOwner(Ship* owner) {mOwnerType = owner->getType();}
	GameObjectType getOwnerType() {return mOwnerType;}

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

	unsigned getPrefabID() const {return prefabID;}
//	virtual bool receiveDamage( unsigned int damages, Vector3 fromDirection = Vector3(0,0,0 )) {mDeadFlag = false;}

private:
	unsigned mPower;
	unsigned prefabID;
	GameObjectType mOwnerType;
	TimeToLiveComponent mTTLComponent;
};
