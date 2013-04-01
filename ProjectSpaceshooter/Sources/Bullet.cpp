
/************************************************************************/
/* BulletPrefab class                                                   */
/************************************************************************/
BulletPrefab::BulletPrefab( unsigned prefabID ) : mPrefabID(prefabID)
{

}







/************************************************************************/
/* Bullet class                                                         */
/************************************************************************/
Bullet::Bullet() : GameObject()
{
	mTTLComponent.setTimeToLive(3000);
}

Bullet::Bullet( std::string meshName, Ogre::SceneManager* sceneMgr ) : GameObject(meshName, sceneMgr)
{
	mTTLComponent.setTimeToLive(3000);
}

Bullet::Bullet( BulletPrefab * objectTemplate, Ogre::SceneManager * _sceneMenager )
	: GameObject(objectTemplate->getMeshName(), _sceneMenager), 
		mPower(objectTemplate->getBulletPower())
{
	mPhysicsComponent.setMaxVelocityValue( objectTemplate->getMaxVelocity() );
	mPhysicsComponent.setVelocity( objectTemplate->getVelocityVector() );
	mTTLComponent.setTimeToLive(3000);
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
