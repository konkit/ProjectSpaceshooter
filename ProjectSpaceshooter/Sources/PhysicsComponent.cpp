

float PhysicsComponent::getRotVelocity()
{
	return rotVelocity;
}

Ogre::Vector3 PhysicsComponent::getCurrentVelocity()
{
	return currentVelocity;
}

void PhysicsComponent::setRotVelocity( float newRotVelocity )
{
	rotVelocity = newRotVelocity * rotVelocityValue;
}

void PhysicsComponent::forceRotVelocity(float newRotVelocity)	{
	rotVelocity = newRotVelocity;
}

void PhysicsComponent::setCurrentVelocity( Ogre::Vector3 const& newVelocity )
{
	currentVelocity = newVelocity;
}

void PhysicsComponent::setMaxVelocityValue( float newVelocity )
{
	maxVelocityValue = newVelocity;
}

PhysicsComponent::PhysicsComponent()
	: currentVelocity(0.0, 0.0, 0.0), 
	  rotVelocity(0.0),
	  rotVelocityValue(2.0), 
	  accelerationValue(5.0),
	  maxVelocityValue(700.0)
{

}

PhysicsComponent::PhysicsComponent(const MovablePrefab * prefab )
	:	rotVelocity(0.0),
		rotVelocityValue(2.0)
{
	maxVelocityValue = prefab->getMaxVelocity();
	mMaxAngleVelocity = prefab->getMaxAngleVelocity();
	accelerationValue = prefab->getMaxAcceleration();
}

void PhysicsComponent::updateVelocity() {

	//get difference vector between current velocity and target velocity
	Ogre::Vector3 diffVector = targetVelocity - currentVelocity;

	//scale this vector to be equal to acceleration in magnitude
	if( diffVector.length() > accelerationValue )
	{
		diffVector.normalise();
		diffVector = diffVector * accelerationValue;
	}

	//change current velocity by this vector
	currentVelocity += diffVector;
}

void PhysicsComponent::setTargetVelocity( Ogre::Quaternion orientation, Ogre::Vector3 localDir )
{
	targetVelocity = maxVelocityValue * ( orientation * localDir );
}

void PhysicsComponent::AddVectorToCurrentVelocity( Ogre::Vector3 addedVector )
{
	currentVelocity += addedVector;
}

void PhysicsComponent::setFromPrefab( const MovablePrefab * prefab )
{
	maxVelocityValue = prefab->getMaxVelocity();
	mMaxAngleVelocity = prefab->getMaxAngleVelocity();
	accelerationValue = prefab->getMaxAcceleration();
}
