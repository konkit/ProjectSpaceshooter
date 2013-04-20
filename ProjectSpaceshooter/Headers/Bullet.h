#pragma once

#include "GameObject.h"
#include "TimeToLiveComponent.h"
#include "Prefabs.h"


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
	GameObject* getOwner();

	bool isDead();

	TimeToLiveComponent& getTTLComponent();

	void setCurrentSpeedToMax() { mPhysicsComponent.setCurrentSpeedToMax(); }

	GameObjectType getType() {
		return GameObjectType::bulletObject;
	}

private:
	float mPower;
	GameObject* mOwner;
	TimeToLiveComponent mTTLComponent;
};
