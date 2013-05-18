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
	PhysicsComponent();
	PhysicsComponent(const MovablePrefab * prefab);

	//sets maximum length of velocity vector
	void setMaxVelocityValue(float newVelocity);
	float getMaxVelocityValue()	{
		return maxVelocityValue;
	}


	//sets new instantaneous velocity vector 
	void setCurrentVelocity(Ogre::Vector3 const& newVelocity);

	//gets current instantaneous velocity vector 
	Ogre::Vector3 getCurrentVelocity();

	//Adds vector to current instantaneous velocity vector
	//usable for example in shockwave
	void AddVectorToCurrentVelocity( Ogre::Vector3 addedVector );

	//set angular velocity (it is multiplied inside by maximum rotation velocity)
	void setRotVelocity(float newRotVelocity);
	//
	float getTargetRotVelocity()	{
		return targetRotVelocityValue;
	}


	void forceRotVelocity(float newRotVelocity);

	void setMovement(Ogre::Quaternion orientation,bool forward, bool backward, bool left, bool right)	{
		float value;
		if( forward == true)	
			value = 1.0;
		if( backward == true)
			value = -1.0;
		
		setTargetVelocityValue( value );
	}

	void setRotation(bool clockwise, bool counterClockwise)	{
		float angle = 0.0;

		if( clockwise == true )
			angle -= maxRotVelocityValue;

		if( counterClockwise == true )	
			angle += maxRotVelocityValue;
		
		if( clockwise == false && counterClockwise == false)
			angle = 0.0f;

		setRotVelocity(angle);
	}


	//get angular velocity
	float getRotVelocity();

	//Sets target velocity vector to which current velocity vector is progressively approaching.
	void setTargetVelocityValue( float value );
	//Gets target velocity vector to which current velocity vector is progressively approaching.
	float getTargetVelocityValue() { return targetVelocityValue; }

	//Updates currentVelocity vector (acceleration, approaching to target velocity etc.)
	void updateVelocity(Ogre::Vector3 forwardVector,float  deltaTime);
	void updateRotation(float deltaTime);


	//instantly sets current velocity to target velocity value.
	void setCurrentSpeedToMax(Ogre::Vector3 forwardVector) {
		currentVelocity = forwardVector * maxVelocityValue;
	}

	//sets new acceleration value
	void setAccelerationValue(float newAccelerationValue) {
		accelerationValue = newAccelerationValue;
	}
	void setFromPrefab( const MovablePrefab * prefab );
	unsigned getCurrentVelocityValue();

	float getRotVelocityValue()	{
		return rotVelocityValue;
	}


private:
	Ogre::Vector3 currentVelocity;
	float rotVelocityValue;

	float maxVelocityValue;
	float maxRotVelocityValue;

	float accelerationValue;
	float rotAccelerationValue;

	float targetVelocityValue;
	float targetRotVelocityValue;

	//@author Zyga
	float mMaxAngleVelocity; //czy to wgl. jest potrzebne?
};