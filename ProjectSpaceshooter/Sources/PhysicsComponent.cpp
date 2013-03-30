
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

PhysicsComponent::PhysicsComponent() : velocity(0.0, 0.0, 0.0), rotVelocity(0.0),
	velocityValue(700.0), rotVelocityValue(2.0)
{

}

