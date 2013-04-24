/************************************************************************/
/* Bullet class                                                         */
/************************************************************************/
#include "Bullet.h"
Bullet::Bullet() : GameObject()
{
	mTTLComponent.setTimeToLive(300);
	cout << "Create bullet object\n";
}

Bullet::Bullet( std::string meshName, Ogre::SceneManager* sceneMgr ) : GameObject(meshName, sceneMgr)
{
	mTTLComponent.setTimeToLive(3.00);
	cout << "Create bullet object\n";
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


Bullet::~Bullet()
{
	cout << "Destroy bullet object\n";
}
