/************************************************************************/
/* Bullet class                                                         */
/************************************************************************/
Bullet::Bullet() : GameObject()
{
	mTTLComponent.setTimeToLive(300);
}

Bullet::Bullet( std::string meshName, Ogre::SceneManager* sceneMgr ) : GameObject(meshName, sceneMgr)
{
	mTTLComponent.setTimeToLive(300);
}

Bullet::Bullet( BulletPrefab * objectTemplate, Ogre::SceneManager * _sceneMenager )
	: GameObject(objectTemplate->getMeshName(), _sceneMenager), 
		mPower(objectTemplate->getBulletPower())
{
	mPhysicsComponent.setMaxVelocityValue( objectTemplate->getMaxVelocity() );
	mPhysicsComponent.setVelocity( Vector3(0.0f, 0.0f, 1.0f));
	mTTLComponent.setTimeToLive(300);
}

TimeToLiveComponent& Bullet::getTTLComponent()
{
	return mTTLComponent;
}

bool Bullet::isDead()
{
	if( mTTLComponent.isTimeIsUp()==true )
		return true;
	if( GameObject::isDead() == true )
		return true;

	return false;
}

void Bullet::setOwner( GameObject* owner )
{
	mOwner = owner;
}

void Bullet::setPower( float newPower )
{
	mPower = newPower;
}

float Bullet::getPower()
{
	return mPower;
}
