/************************************************************************/
/* Bullet class                                                         */
/************************************************************************/
#include "Bullet.h"

Bullet::Bullet(const BulletPrefab * objectTemplate, Ogre::SceneManager * _sceneMenager )
	: GameObject(objectTemplate, _sceneMenager), GameObject_WithCollider(objectTemplate, _sceneMenager), GameObject_Movable(objectTemplate, _sceneMenager),
		mPower(objectTemplate->getBulletPower())
{
	mPhysicsComponent.setMaxVelocityValue( objectTemplate->getMaxVelocity() );
	mPhysicsComponent.setCurrentVelocity( Vector3(0.0f, 0.0f, 1.0f));
	mTTLComponent.setTimeToLive(objectTemplate->getTTL());
	prefabID = objectTemplate->getPrefabID();
}

TimeToLiveComponent& Bullet::getTTLComponent()
{
	return mTTLComponent;
}


Bullet::~Bullet()
{
}
