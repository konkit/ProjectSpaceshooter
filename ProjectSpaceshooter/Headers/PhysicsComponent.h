#pragma once


/** 
  *
  * @author konkit
  */

class PhysicsComponent
{
public:
	PhysicsComponent();

	void setMaxVelocityValue(float newVelocity);
	void setVelocity(Ogre::Vector3 const& newVelocity);

	void setRotVelocity(float newRotVelocity);

	Ogre::Vector3 getVelocity();

	float getRotVelocity();

	void setVelocityValue(float newValue);
	float getVelocityValue();

private:
	Ogre::Vector3 velocity;
	float rotVelocity;

	float velocityValue;
	float rotVelocityValue;
};