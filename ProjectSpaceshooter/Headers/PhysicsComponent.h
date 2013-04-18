#pragma once


/** 
  *
  * @author konkit
  */

class PhysicsComponent
{
public:
	PhysicsComponent();

	//sets maximum length of velocity vector
	void setMaxVelocityValue(float newVelocity);
	//sets new velocity vector 
	void setVelocity(Ogre::Vector3 const& newVelocity);

	void setRotVelocity(float newRotVelocity);

	Ogre::Vector3 getVelocity();

	float getRotVelocity();

	void updateVelocity();

	void setTargetVelocity( Ogre::Quaternion orientation,  Ogre::Vector3 localDir );
	Ogre::Vector3 getTargetVelocity() { return targetVelocity; }

	void setMaxSpeed() {
		velocity = targetVelocity;
	}

private:
	Ogre::Vector3 velocity;
	float rotVelocity;

	float maxVelocityValue;
	float rotVelocityValue;

	float accelerationValue;
	Ogre::Vector3 targetVelocity;
};