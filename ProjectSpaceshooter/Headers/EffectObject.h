#pragma once
#include "Prefabs.h"
#include "TimeToLiveComponent.h"

using namespace std;;
class EffectObject : public GameObject_WithCollider
{
public:
	EffectObject() : GameObject(), power(0)
	{
		mTTLComponent.setTimeToLive(3.00);
	}

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
	{
	}

	TimeToLiveComponent& getTTLComponent() {
		return mTTLComponent;
	}

	bool isDead()
	{
		if( mTTLComponent.isTimeIsUp()==true )
			return true;

		return false;
	}

	GameObjectType getType() {
		return GameObjectType::effectObject;
	}

	virtual bool receiveDamage( unsigned int damages, Vector3 fromDirection ) 
	{
		return false;
	}

	unsigned getPower() 
	{
		return unsigned((double) power * mTTLComponent.percentOfLeftTime());
	}
	void setPower(unsigned val) { power = val; }
private:
	TimeToLiveComponent mTTLComponent;
	unsigned power;
};