/************************************************************************/
/* Bullet class                                                         */
/************************************************************************/
#include "Bullet.h"
Bullet::Bullet() : GameObject()
{
	mTTLComponent.setTimeToLive(300);
}

Bullet::Bullet( std::string meshName, Ogre::SceneManager* sceneMgr ) : GameObject(meshName, sceneMgr)
{
	mTTLComponent.setTimeToLive(3.00);
}

Bullet::Bullet(const BulletPrefab * objectTemplate, Ogre::SceneManager * _sceneMenager )
	: GameObject(objectTemplate, _sceneMenager), GameObject_WithCollider(objectTemplate, _sceneMenager), GameObject_Movable(objectTemplate, _sceneMenager),
		mPower(objectTemplate->getBulletPower())
{
	mPhysicsComponent.setMaxVelocityValue( objectTemplate->getMaxVelocity() );
	mPhysicsComponent.setCurrentVelocity( Vector3(0.0f, 0.0f, 1.0f));
	mTTLComponent.setTimeToLive(3.00);
}

TimeToLiveComponent& Bullet::getTTLComponent()
{
	return mTTLComponent;
}


void Bullet::setOwner( GameObject* owner )
{
	mOwner = owner;
}

GameObject* Bullet::getOwner()
{
	return mOwner;
}
