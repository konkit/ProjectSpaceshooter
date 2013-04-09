
float PhysicsComponent::getVelocityValue()
{
	return velocityValue;
}

void PhysicsComponent::setVelocityValue( float newValue )
{
	velocityValue = newValue;
}

float PhysicsComponent::getRotVelocity()
{
	return rotVelocity;
}

Ogre::Vector3 PhysicsComponent::getVelocity()
{
	return velocity;
}

void PhysicsComponent::setRotVelocity( float newRotVelocity )
{
	rotVelocity = newRotVelocity * rotVelocityValue;
}

void PhysicsComponent::setVelocity( Ogre::Vector3 const& newVelocity )
{
	velocity = newVelocity * velocityValue;
}

void PhysicsComponent::setMaxVelocityValue( float newVelocity )
{
	velocityValue = newVelocity;
}

PhysicsComponent::PhysicsComponent()
	: velocity(0.0, 0.0, 0.0), 
	  rotVelocity(0.0),
	  velocityValue(300.0),
	  rotVelocityValue(2.0), 
	  //acceleration(100.0), 
	  accelerationValue(100.0),
	  maxVelocityValue(700.0)
{

}

void PhysicsComponent::updateVelocity() {
	//temporary
	//velocity += acceleration;

	//get difference vector between current velocity and target velocity
	Ogre::Vector3 diffVector = targetVelocity - velocity;

	//scale this vector to be equal to acceleration in magnitude
	diffVector.normalise();
	diffVector = diffVector * accelerationValue;

	//change current velocity by this vector
	velocity += diffVector;
}

void PhysicsComponent::setTargetVelocity( Ogre::Quaternion orientation, Ogre::Vector3 localDir )
{
	targetVelocity = maxVelocityValue * ( orientation * localDir );
}