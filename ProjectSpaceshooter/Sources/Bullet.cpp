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
	mTTLComponent.setTimeToLive(300);
}

Bullet::Bullet(const BulletPrefab * objectTemplate, Ogre::SceneManager * _sceneMenager )
	: GameObject(objectTemplate, _sceneMenager), GameObject_WithColider(objectTemplate, _sceneMenager), GameObject_Movable(objectTemplate, _sceneMenager),
		mPower(objectTemplate->getBulletPower())
{
	
	mTTLComponent.setTimeToLive(300);
}

TimeToLiveComponent& Bullet::getTTLComponent()
{
	return mTTLComponent;
}


void Bullet::setOwner( GameObject* owner )
{
	mOwner = owner;
}
