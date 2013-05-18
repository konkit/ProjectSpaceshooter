#include "PhysicsComponent.h"


PhysicsComponent::PhysicsComponent()
	: currentVelocity(0.0, 0.0, 0.0), 
	  rotVelocityValue(0.0),
	  maxRotVelocityValue(2.0), 
	  accelerationValue(5.0),
	  rotAccelerationValue(0.05),
	  maxVelocityValue(700.0),
	  targetVelocityValue(0),
	  targetRotVelocityValue(0.0)
{

}

PhysicsComponent::PhysicsComponent(const MovablePrefab * prefab )
	:   currentVelocity(0.0, 0.0, 0.0),	
	   rotVelocityValue(0.0),
	   targetVelocityValue(0),
	   rotAccelerationValue(2.00),
	   targetRotVelocityValue(0.0)
{
	maxVelocityValue = prefab->getMaxVelocity();
	maxRotVelocityValue = prefab->getMaxAngleVelocity();
	accelerationValue = prefab->getMaxAcceleration();
}

float PhysicsComponent::getRotVelocityValue()
{
	return rotVelocityValue;
}

Ogre::Vector3 PhysicsComponent::getCurrentVelocity()
{
	return currentVelocity;
}

void PhysicsComponent::setTargetRotVelocity( float newRotVelocity )
{
	//rotVelocity = newRotVelocity > rotVelocityValue ? rotVelocityValue : newRotVelocity;
	targetRotVelocityValue = newRotVelocity * maxRotVelocityValue;
}

void PhysicsComponent::setCurrentVelocity( Ogre::Vector3 const& newVelocity )
{
	currentVelocity = newVelocity;
}

void PhysicsComponent::setMaxVelocityValue( float newVelocity )
{
	maxVelocityValue = newVelocity;
}



void PhysicsComponent::updateVelocity(Ogre::Vector3 forwardVector, float deltaTime) {

	//get difference vector between current velocity and target velocity
	Ogre::Vector3 diffVector = forwardVector*targetVelocityValue - currentVelocity;

	//scale this vector to be equal to acceleration in magnitude
	if( diffVector.length() > ( accelerationValue * deltaTime ) )
	{
		diffVector.normalise();
		diffVector = diffVector * ( accelerationValue * deltaTime );
	}

	//change current velocity by this vector
	currentVelocity += diffVector;
}

void PhysicsComponent::updateRotation(float deltaTime)	{
	//Calculating rotation velocity
	float diffRotVelocity = targetRotVelocityValue - rotVelocityValue;

	if( abs(diffRotVelocity) < abs(rotAccelerationValue * deltaTime) )	{
		rotVelocityValue += diffRotVelocity;
	} else 
	if( diffRotVelocity > 0.00001 )	{
		rotVelocityValue += rotAccelerationValue * deltaTime;
	} else if( diffRotVelocity < -0.00001) {
		rotVelocityValue -= rotAccelerationValue * deltaTime;
	}

}


void PhysicsComponent::setTargetVelocityValue( float value )
{
	targetVelocityValue = value * maxVelocityValue;
}

void PhysicsComponent::AddVectorToCurrentVelocity( Ogre::Vector3 addedVector )
{
	currentVelocity += addedVector;
}

void PhysicsComponent::setFromPrefab( const MovablePrefab * prefab )
{
	currentVelocity = Vector3(0.0, 0.0, 0.0);	
	targetVelocityValue  = 0.0;
	rotVelocityValue = 0.0;
	maxRotVelocityValue = prefab->getMaxAngleVelocity();
	maxVelocityValue = prefab->getMaxVelocity();
	accelerationValue = prefab->getMaxAcceleration();

}

unsigned PhysicsComponent::getCurrentVelocityMagnitude()
{
	return currentVelocity.squaredLength();
}
