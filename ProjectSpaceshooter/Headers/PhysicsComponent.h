#pragma once
#include "Prefabs.h"


/** This component is part of movable game objects 
  * It takes care about velocities, acceleration 
  * and that sort of physics.
  *
  * @author konkit
  */

class PhysicsComponent
{
public:
	//Constructors, init functions, etc.
	PhysicsComponent();
	PhysicsComponent(const MovablePrefab * prefab);

	void setFromPrefab( const MovablePrefab * prefab );
	
	////////////////////////////////////////////////////////////////////////////////
	// Movement functions                   
	////////////////////////////////////////////////////////////////////////////////

	//Maximum speed functions

	// sets maximum speed to specified values
	void setMaxVelocityValue(float newVelocity);
	// returns current maximum speed of object
	float getMaxVelocityValue()	{	return maxVelocityValue;}


	//World coordinate velocity vector accessor functions

	// sets absolute, world-coordinate velocity to specified vector value
	void setCurrentVelocity(Ogre::Vector3 const& newVelocity);
	// returns current absolute, world-coordinate velocity vector
	Ogre::Vector3 getCurrentVelocity();
	// returns length of velocity vector
	float getCurrentVelocityMagnitude();


	//Target velocity functions

	// sets target velocity value to which current velocity is approaching every update
	void setTargetVelocityValue( float value );
	// gets target velocity value to which current velocity is approaching every update
	float getTargetVelocityValue() { return targetVelocityValue; }
	// increase target velocity value by some value
	void increaseTargetVelocityValue(float value)	{	
		if( abs(targetVelocityValue + value ) < maxVelocityValue  )
			targetVelocityValue += value;
	}



	//Acceleration functions

	//Sets new acceleration value - value which velocity is changing every update
	void setAccelerationValue(float newAccelerationValue) {
		accelerationValue = newAccelerationValue;
	}


	//Other movement functions 

	//Adds vector to current instantaneous velocity vector
	//usable for example in shockwave
	void AddVectorToCurrentVelocity( Ogre::Vector3 addedVector );

	//instantly sets current velocity to max velocity value.
	void setCurrentSpeedToMax(Ogre::Vector3 forwardVector) {
		currentVelocity = forwardVector * maxVelocityValue;
	}

	//Updates velocity vector (acceleration etc.)
	void updateVelocity(Ogre::Vector3 forwardVector,float  deltaTime);


	

	//////////////////////////////////////////////////////////////////////////////////
	// Rotation functions                  
	////////////////////////////////////////////////////////////////////////////////

	//target rotation velocity functions

	// sets new target rotation value - rotation velocity is approaching to this value every update
	void setTargetRotVelocity(float newRotVelocity);
	// gets current target rotation value - rotation velocity is approaching to this value every update
	float getTargetRotVelocity() {	return targetRotVelocityValue;	}


	//absolute rotation velocity functions
	
	//returns actual rotation velocity value
	float getRotVelocityValue();


	//other rotation functions

	//Updates rotation velocity (acceleration etc.)
	void updateRotation(float deltaTime);



private:
	//world coordinates velocities
	Ogre::Vector3 currentVelocity;
	float rotVelocityValue;

	//maximum values of velocities
	float maxVelocityValue;
	float maxRotVelocityValue;

	//acceleration values
	float accelerationValue;
	float rotAccelerationValue;

	//target values
	float targetVelocityValue;
	float targetRotVelocityValue;
};