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
	void forceRotVelocity(float newRotVelocity);

	//get angular velocity
	float getRotVelocity();

	//Sets target velocity vector to which current velocity vector is progressively approaching.
	void setTargetVelocity( Ogre::Quaternion orientation,  Ogre::Vector3 localDir );
	//Gets target velocity vector to which current velocity vector is progressively approaching.
	Ogre::Vector3 getTargetVelocity() { return targetVelocity; }

	//Updates currentVelocity vector (acceleration, approaching to target velocity etc.)
	void updateVelocity();

	//instantly sets current velocity to target velocity value.
	void setCurrentSpeedToMax() {
		currentVelocity = targetVelocity;
	}

	//sets new acceleration value
	void setAccelerationValue(float newAccelerationValue) {
		accelerationValue = newAccelerationValue;
	}
	void setFromPrefab( const MovablePrefab * prefab );
private:
	Ogre::Vector3 currentVelocity;
	float rotVelocity;

	float maxVelocityValue;
	float rotVelocityValue;

	float accelerationValue;
	Ogre::Vector3 targetVelocity;

	//@author Zyga
	float mMaxAngleVelocity; //czy to wgl. jest potrzebne?
};