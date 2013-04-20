#pragma once


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

	//sets maximum length of velocity vector
	void setMaxVelocityValue(float newVelocity);

	//sets new instantaneous velocity vector 
	void setVelocity(Ogre::Vector3 const& newVelocity);
	Ogre::Vector3 getVelocity();

	//set angular velocity
	void setRotVelocity(float newRotVelocity);
	float getRotVelocity();

	void setTargetVelocity( Ogre::Quaternion orientation,  Ogre::Vector3 localDir );
	Ogre::Vector3 getTargetVelocity() { return targetVelocity; }


	void updateVelocity();



	void setCurrentSpeedToMax() {
		velocity = targetVelocity;
	}

	void setAccelerationValue(float newAccelerationValue) {
		accelerationValue = newAccelerationValue;
	}

private:
	Ogre::Vector3 velocity;
	float rotVelocity;

	float maxVelocityValue;
	float rotVelocityValue;

	float accelerationValue;
	Ogre::Vector3 targetVelocity;
};