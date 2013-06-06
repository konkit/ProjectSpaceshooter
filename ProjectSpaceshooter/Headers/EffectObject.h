#pragma once
#include "Prefabs.h"
#include "TimeToLiveComponent.h"

using namespace std;;

/** GameObject representing explosions and other special effects
  *
  * @author Zyga
  */

class EffectObject : public GameObject_WithCollider
{
public:
	/** Sets initial values */
	EffectObject() : GameObject(), power(0)
	{
		mTTLComponent.setTimeToLive(3.00);
	}

	/** Loads data of effect from prefab 
	  * @param objectTemplate - pointer to prefab object which stores data about object
	  * @param _sceneMgr - Ogre::SceneManager object for this current state
*/
	EffectObject( EffectPrefab * objectTemplate, Ogre::SceneManager * _sceneMgr)
		: GameObject(), GameObject_WithCollider(objectTemplate, _sceneMgr), power(objectTemplate->getPower())
	{
		mTTLComponent.setTimeToLive(objectTemplate->getTTL());
		uniqueID++;
		//Custom settings of SceneNode because of being a Particle System, not a Entity (mesh)

		//Creation of particle system
		Ogre::ParticleSystem* particleSystem;
			std::string uniqueName = std::to_string(uniqueID);
			particleSystem = _sceneMgr->createParticleSystem(uniqueName, objectTemplate->getParticleSystemName() );
			//particleSystem->fastForward(1.0);
			//particleSystem->setSpeedFactor(3.0);
		mNode = _sceneMgr->getRootSceneNode()->createChildSceneNode();
		mNode->attachObject( particleSystem );
	}

	~EffectObject()
	{	}

	/** returns Time To Live component 
	  * @return TimeToLiveComponent
	  */
	TimeToLiveComponent& getTTLComponent() {
		return mTTLComponent;
	}

	/** checks if effect should dissapear
	  * @return bool - true if dead
	  */
	bool isDead()
	{
		if( mTTLComponent.isTimeIsUp()==true )
			return true;

		return false;
	}

	/** implementation of getType virtual method from GameObject class 
	  * @return GameObjectType - type of this object (in this case: effectObject)
	  */
	GameObjectType getType() {
		return GameObjectType::effectObject;
	}


	virtual bool receiveDamage( unsigned int damages, Vector3 fromDirection ) 
	{
		return false;
	}

	/** returns power of the damage dealt within area of this effect
	  * @return unsigned power of damage of effect
	  */
	unsigned getPower() 
	{
		return unsigned((double) power * mTTLComponent.percentOfLeftTime());
	}

	/** sets new power of effect */
	void setPower(unsigned val) { power = val; }

	friend ostream& operator<< ( ostream & stream, EffectObject& object)	{
		return stream<<"Effect ("<<object.getPosition()<<") ";
	}

private:
	TimeToLiveComponent mTTLComponent;
	unsigned power;
};