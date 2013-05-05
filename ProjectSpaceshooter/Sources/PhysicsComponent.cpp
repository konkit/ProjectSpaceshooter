

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
	//rotVelocity = newRotVelocity > rotVelocityValue ? rotVelocityValue : newRotVelocity;
	targetRotVelocity = newRotVelocity;
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
	  rotAcceleration(0.05),
	  maxVelocityValue(700.0),
	  targetVelocity(0,0,0),
	  targetRotVelocity(0.0)
{

}

PhysicsComponent::PhysicsComponent(const MovablePrefab * prefab )
	:   currentVelocity(0.0, 0.0, 0.0),	
	    rotVelocity(0.0),
	   targetVelocity(0,0,0),
	   rotAcceleration(2.00),
	   targetRotVelocity(0.0)
{
	maxVelocityValue = prefab->getMaxVelocity();
	rotVelocityValue = prefab->getMaxAngleVelocity();
	accelerationValue = prefab->getMaxAcceleration();
}

void PhysicsComponent::updateVelocity(float deltaTime) {

	//get difference vector between current velocity and target velocity
	Ogre::Vector3 diffVector = targetVelocity - currentVelocity;

	//scale this vector to be equal to acceleration in magnitude
	if( diffVector.length() > ( accelerationValue * deltaTime ) )
	{
		diffVector.normalise();
		diffVector = diffVector * ( accelerationValue * deltaTime );
	}

	//change current velocity by this vector
	currentVelocity += diffVector;

	//Calculating rotation velocity
	float diffRotVelocity = targetRotVelocity - rotVelocity;

	if( abs(diffRotVelocity) < abs(rotAcceleration * deltaTime) )	{
		rotVelocity += diffRotVelocity;
	} else 
	if( diffRotVelocity > 0.00001 )	{
		rotVelocity += rotAcceleration * deltaTime;
	} else if( diffRotVelocity < -0.00001) {
		rotVelocity -= rotAcceleration * deltaTime;
	}



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
	currentVelocity = Vector3(0.0, 0.0, 0.0);	
	targetVelocity  = Vector3(0.0, 0.0, 0.0);
	rotVelocity = 0.0;
	rotVelocityValue = prefab->getMaxAngleVelocity();
	maxVelocityValue = prefab->getMaxVelocity();
	accelerationValue = prefab->getMaxAcceleration();

}

unsigned PhysicsComponent::getCurrentVelocityValue()
{
	return maxVelocityValue; // TODO Change to current Value
}
