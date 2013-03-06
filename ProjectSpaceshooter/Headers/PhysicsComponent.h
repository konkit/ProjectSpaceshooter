#pragma once

class PhysicsComponent
{
public:
	PhysicsComponent() : velocity(0.0, 0.0, 0.0), rotVelocity(0.0),
		velocityValue(0.1), rotVelocityValue(0.01)
	{	}

	void setVelocity(Ogre::Vector3 const& newVelocity)	{
		velocity = newVelocity * velocityValue;
	}

	void setRotVelocity(float newRotVelocity)	{
		rotVelocity = newRotVelocity * rotVelocityValue;
	}

	Ogre::Vector3 getVelocity()	{
		return velocity;
	}

	float getRotVelocity()	{
		return rotVelocity;
	}

private:
	Ogre::Vector3 velocity;
	float rotVelocity;

	float velocityValue;
	float rotVelocityValue;
};