#pragma once

class PhysicsComponent
{
public:
	PhysicsComponent() : velocity(0.0, 0.0, 0.0), rotVelocity(0.0)	{

	}

	void setVelocity(Ogre::Vector3 const& newVelocity)	{
		velocity = newVelocity;
	}

	void setRotVelocity(float newRotVelocity)	{
		rotVelocity = newRotVelocity;
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
};