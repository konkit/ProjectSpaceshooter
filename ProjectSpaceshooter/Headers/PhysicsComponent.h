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
	/**
	* Constructors, init functions, etc.
	* @author konkit
	*/
	PhysicsComponent();
	/**
	* Constructors, init functions, etc.
	* @param prefab initialized with this prefab
	* @author konkit
	*/
	PhysicsComponent(const MovablePrefab * prefab);

	/**
	*
	* @param prefab 
	* @author konkit
	*/
	void setFromPrefab( const MovablePrefab * prefab );
	
	////////////////////////////////////////////////////////////////////////////////
	// Movement functions                   
	////////////////////////////////////////////////////////////////////////////////

		/**
		* Maximum speed functions
		* @param newVelocity sets maximum speed to specified values  
		* @author konkit
		*/
		void setMaxVelocityValue(float newVelocity);
		/**
		* @return current maximum speed of object 
		* @author konkit
		*/
		float getMaxVelocityValue()	{	return maxVelocityValue;}

	//World coordinate velocity vector accessor functions

		/**
		* sets absolute, world-coordinate velocity to specified vector value
		* @param newVelocity 
		* @author konkit
		*/
		void setCurrentVelocity(Ogre::Vector3 const& newVelocity);
		/**
		* @return current absolute, world-coordinate velocity vector
		* @author konkit
		*/
		Ogre::Vector3 getCurrentVelocity();
		/**
		* @return length of velocity vector 
		* @author konkit
		*/
		float getCurrentVelocityMagnitude();

	//Target velocity functions

		/**
		* sets target velocity value to which current velocity is approaching every update 
		* @param value 
		* @author konkit
		*/
		void setTargetVelocityValue( float value );
		/**
		* gets target velocity value to which current velocity is approaching every update 
		* @author konkit
		*/
		float getTargetVelocityValue() { return targetVelocityValue; }
		/**
		* increase target velocity value by some value 
		* @param value 
		* @author konkit
		*/
		void increaseTargetVelocityValue(float value)	{	
			if( abs(targetVelocityValue + value ) < maxVelocityValue  )
				targetVelocityValue += value;
		}

	//Acceleration functions

		/**
		* Sets new acceleration value - value which velocity is changing every update s
		* @param newAccelerationValue 
		* @author konkit
		*/
		void setAccelerationValue(float newAccelerationValue) {
			accelerationValue = newAccelerationValue;
		}

	//Other movement functions 

		/**
		* Adds vector to current instantaneous velocity vector 
		* usable for example in shockwave 
		* @param addedVector 
		* @author konkit
		*/
		void AddVectorToCurrentVelocity( Ogre::Vector3 addedVector );

		/**
		* instantly sets current velocity to max velocity value.
		* @param forwardVector 
		* @author konkit
		*/
		void setCurrentSpeedToMax(Ogre::Vector3 forwardVector) {
			currentVelocity = forwardVector * maxVelocityValue;
		}

		/**
		* Updates velocity vector (acceleration etc.)
		* @param forwardVector 
		* @param deltaTime 
		* @author Zyga
		*/
		void updateVelocity(Ogre::Vector3 forwardVector,float  deltaTime);


	

	//////////////////////////////////////////////////////////////////////////////////
	// Rotation functions                  
	////////////////////////////////////////////////////////////////////////////////

	//target rotation velocity functions

		/**
		* sets new target rotation value - rotation velocity is approaching to this value every update 
		* @param newRotVelocity 
		* @author konkit
		*/
		void setTargetRotVelocity(float newRotVelocity);
		/**
		* gets current target rotation value - rotation velocity is approaching to this value every update 
		* @author konkit
		*/
		float getTargetRotVelocity() {	return targetRotVelocityValue;	}

	//absolute rotation velocity functions

		/**
		* @return actual rotation velocity value
		* @author konkit
		*/
		float getRotVelocityValue();

	//other rotation functions

		/**
		* Updates rotation velocity (acceleration etc.)
		* @param deltaTime 
		* @author Zyga
		*/
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